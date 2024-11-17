#include <Geode/modify/PlayLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-2123456789)

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("PlayLayer::setupHasCompleted", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("PlayLayer::toggleGlitter", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("PlayLayer::postUpdate", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("PlayLayer::addObject", PREFERRED_HOOK_PRIO);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
		bool performHideTwoPlayerGuide = false;
		bool foundPlayerOrAudioEffectsLayer = false;
		bool foundHitboxNodeTwoPlayerGuide = false;
		bool foundHitboxNode = false;
	};
	bool isIn(std::vector<int> numberStorage, int id) {
		return std::ranges::find(numberStorage, id) != numberStorage.end();
	}
	void addObject(GameObject* object) {
		if (!Utils::modEnabled()) return PlayLayer::addObject(object);
		if (const std::string& noGlow = Utils::getString("noGlow"); noGlow != "Ignore") {
			object->m_hasNoGlow = noGlow == "Force Enable"; // this has to go here because putting it in setupHasCompleted causes objects at camera's starting position to already have glow enabled
		}
		if (isIn(m_fields->manager->particleObjects, object->m_objectID)) return PlayLayer::addObject(object);
		// truth be told, i could've done a switch case based on enum value. however, actual objects with noTouch property would be unaffected
		if (Utils::getBool("noGoldCoinParticles") && object->m_objectID == 142) object->m_hasParticles = false;
		else if (Utils::getBool("noCoinParticles") && object->m_objectID == 1329) object->m_hasNoParticles = true;
		else if (Utils::getBool("noCustomOrbParticles") && object->m_objectID == 1594) object->m_particleString = "";
		else if (Utils::getBool("noTeleportOrbParticles") && object->m_objectID == 3027) object->m_particleString = "";
		else if (Utils::getBool("noDashOrbParticles") && (object->m_objectID == 1704 || object->m_objectID == 1751)) object->m_particleString = "";
		else if (Utils::getBool("noDualPortalParticles") && (object->m_objectID == 286 || object->m_objectID == 287)) object->m_particleString = "";
		else if (Utils::getBool("noMirrorPortalParticles") && (object->m_objectID == 45 || object->m_objectID == 46)) object->m_particleString = "";
		else if (Utils::getBool("noSizePortalParticles") && (object->m_objectID == 99 || object->m_objectID == 101)) object->m_particleString = "";
		else if (Utils::getBool("noJumpRingParticles") && isIn(m_fields->manager->jumpRingObjects, object->m_objectID)) object->m_particleString = "";
		else if (Utils::getBool("noJumpPadParticles") && isIn(m_fields->manager->jumpPadObjects, object->m_objectID)) object->m_particleString = "";
		else if (Utils::getBool("noGamemodePortalParticles") && isIn(m_fields->manager->gameModePortals, object->m_objectID)) object->m_particleString = "";
		else if (Utils::getBool("noSpeedPortalParticles") && isIn(m_fields->manager->speedPortalObjects, object->m_objectID)) object->m_particleString = "";
		else if (Utils::getBool("noGravityPortalParticles") && isIn(m_fields->manager->gravityPortals, object->m_objectID)) object->m_particleString = "";
		else if (Utils::getBool("noTeleportPortalParticles") && isIn(m_fields->manager->teleportPortalObjects, object->m_objectID)) object->m_particleString = "";
		else if (Utils::getBool("noCollectibleParticles") && isIn(m_fields->manager->collectibleObjects, object->m_objectID)) object->m_particleString = "";
		else if (Utils::getBool("noParticles") && !isIn(m_fields->manager->everythingInOne, object->m_objectID)) object->m_particleString = "";
		PlayLayer::addObject(object);
	}
	void setupHasCompleted() {
		if (!Utils::modEnabled()) return PlayLayer::setupHasCompleted();
		PlayLayer::setupHasCompleted();
		if (m_objects) for (const auto object : CCArrayExt<GameObject*>(m_objects)) {
			if (const std::string &dontEnter = Utils::getString("dontEnter"); dontEnter != "Ignore") {
				object->m_ignoreEnter = dontEnter == "Force Enable";
			}
			if (const std::string &dontFade = Utils::getString("dontFade"); dontFade != "Ignore") {
				object->m_ignoreFade = dontFade == "Force Enable";
			}
			if (const std::string &noAudioScale = Utils::getString("noAudioScale"); noAudioScale != "Ignore") {
				object->m_hasNoAudioScale = noAudioScale == "Force Enable";
			}
			if (const std::string &noEffects = Utils::getString("noEffects"); noEffects != "Ignore") {
				/*
				"Force Disable": force all objects to object->m_hasNoEffects = false regardless of invis status
				"Force Enable": force all objects to object->m_hasNoEffects = true regardless of invis status
				"Force Disable (+ Ignore Invis.)": force an object to object->m_hasNoEffects = false if object is visible
				"Force Enable (+ Ignore Invis.)": force an object to object->m_hasNoEffects = true if object is visible
				"Enable on Visible, Disable on Invis."
				"Disable on Visible, Enable on Invis."

				note: this could be optimized, but i wanted it to be readable source code.
				*/
				if (noEffects == "Enable on Visible, Disable on Invis.") {
					object->m_hasNoEffects = !object->m_isHide && !object->m_isInvisible && object->getOpacity() > 0;
				} else if (noEffects == "Disable on Visible, Enable on Invis.") {
					object->m_hasNoEffects = !(!object->m_isHide && !object->m_isInvisible && object->getOpacity() > 0);
				} else if (utils::string::endsWith(noEffects, " (+ Ignore Invis.)")) {
					// if "(+ Ignore Invis.)" is found at the end, need to perform invis check
					const bool &isInvis = object->m_isHide || object->m_isInvisible || object->getOpacity() <= 0;
					if (!isInvis) object->m_hasNoEffects = utils::string::startsWith(noEffects, "Force Enable ");
				} else {
					// brute force override
					object->m_hasNoEffects = noEffects == "Force Enable";
				}
			}
		}
		if (m_level && m_level->m_twoPlayerMode && Utils::getBool("hideTwoPlayer")) m_fields->performHideTwoPlayerGuide = true;
		if (!std::string(m_level->m_levelString).empty() && m_levelSettings) {
			if (const std::string &fixRobotJump = Utils::getString("fixRobotJump"); fixRobotJump != "Ignore") {
				m_levelSettings->m_fixRobotJump = fixRobotJump == "Force Enable";
			}
			if (const std::string &isFlipped = Utils::getString("isFlipped"); isFlipped != "Ignore") {
				m_levelSettings->m_isFlipped = isFlipped == "Force Enable";
			}
			if (const std::string &enable22Changes = Utils::getString("enable22Changes"); enable22Changes != "Ignore") {
				m_levelSettings->m_enable22Changes = enable22Changes == "Force Enable";
			}
			if (const std::string &dynamicLevelHeight = Utils::getString("dynamicLevelHeight"); dynamicLevelHeight != "Ignore") {
				m_levelSettings->m_dynamicLevelHeight = dynamicLevelHeight == "Force Enable";
			}
			if (const std::string &fixGravityBug = Utils::getString("fixGravityBug"); fixGravityBug != "Ignore") {
				m_levelSettings->m_fixGravityBug = fixGravityBug == "Force Enable";
			}
			if (const std::string &noTimePenalty = Utils::getString("noTimePenalty"); noTimePenalty != "Ignore" && m_level->isPlatformer()) {
				m_levelSettings->m_noTimePenalty = noTimePenalty == "Force Enable";
			}
		}
	}
	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		if (!Utils::modEnabled()) return;
		if (Utils::getBool("noSpeedParticles")) {
			for (const auto &node : CCArrayExt<CCNode*>(this->getChildren())) {
				if (!m_fields->foundHitboxNode) m_fields->foundHitboxNode = node->getID() == "hitbox-node";
				if (!m_fields->foundHitboxNode || node->getZOrder() != 100) continue;
				if (const auto particle = typeinfo_cast<CCParticleSystemQuad*>(node)) particle->setVisible(false);
			}
		}
		const auto batchLayer = this->getChildByIDRecursive("batch-layer");
		if (Utils::getBool("noPlayerParticles") && batchLayer != nullptr) {
			for (const auto &node : CCArrayExt<CCNode*>(batchLayer->getChildren())) {
				if (typeinfo_cast<CCSpriteBatchNode*>(node)) {
					if (m_fields->foundPlayerOrAudioEffectsLayer) {
						m_fields->foundPlayerOrAudioEffectsLayer = false;
						break;
						// player particles are always between AudioEffectsLayer and a CCSpriteBatchNode, and some are ordered after the player. breaking early here for performance reasons
					}
					continue;
				}
				if (!m_fields->foundPlayerOrAudioEffectsLayer) m_fields->foundPlayerOrAudioEffectsLayer = (node == this->m_player1 || node == this->m_player2 || typeinfo_cast<AudioEffectsLayer*>(node));
				if (!m_fields->foundPlayerOrAudioEffectsLayer) continue;
				const auto particle = typeinfo_cast<CCParticleSystemQuad*>(node);
				if (!particle) continue;
				if (particle->getZOrder() == 39 || particle->getZOrder() == 61) {
					/*
					rob was kind enough to set the Z layer of player particles to either 39 or 61! gg
					"ok so why not just hook CCParticleSystem functions lmao why this" --everyone else ever
					it is still necessary to hook postUpdate to know that it's not hiding the wrong particles
					see the typeinfo_cast call at the start of this for loop for more info on breaking out early
					*/
					particle->setVisible(false);
				}
			}
		}
		if (!m_fields->performHideTwoPlayerGuide) return;
		if (Utils::getBool("hideTwoPlayer")) {
			/*
			"omg ery why don't you hook PlayLayer::showTwoPlayerGuide()!! bad geode mod dev!"
			simple: refusing to call the original will cause more issues beyond intended
			also no bindings addresses!!
			*/
			for (const auto &node : CCArrayExt<CCNode*>(getChildren())) {
				if (!m_fields->foundHitboxNodeTwoPlayerGuide) m_fields->foundHitboxNodeTwoPlayerGuide = node->getID() == "hitbox-node";
				if (!m_fields->foundHitboxNodeTwoPlayerGuide) continue;
				if (const auto text = typeinfo_cast<CCLabelBMFont*>(node)) {
					std::string labelString = std::string(text->getString());
					if (labelString != "Player 1" && labelString != "Player 2") continue;
					text->setVisible(false);
					text->setScale(0.0f);
					text->setContentHeight(0.0f);
					text->setContentWidth(0.0f);
					text->setColor({0,0,0});
					text->setOpacity(0);
					text->setZOrder(-2123456789);
					text->setString("");
					text->setPositionX(PREFERRED_HOOK_PRIO);
					text->setPositionY(PREFERRED_HOOK_PRIO);
				} else if (const auto sprite = typeinfo_cast<CCSprite*>(node)) {
					if (typeinfo_cast<CCLabelBMFont*>(sprite)) continue;
					if (cocos::isSpriteFrameName(sprite, "floorLine_001.png")) sprite->setVisible(false);
					m_fields->foundHitboxNodeTwoPlayerGuide = false;
					break;
				}
			}
		}
	}
	void toggleGlitter(bool p0) {
		if (Utils::getBool("noParticlesWhenFlying") && Utils::modEnabled()) return PlayLayer::toggleGlitter(false);
		return PlayLayer::toggleGlitter(p0);
	}
	void onQuit() {
		m_fields->performHideTwoPlayerGuide = false;
		m_fields->foundPlayerOrAudioEffectsLayer = false;
		m_fields->foundHitboxNodeTwoPlayerGuide = false;
		m_fields->foundHitboxNode = false;
		m_fields->manager->endPortalX = 0.0f;
		m_fields->manager->endPortalY = 0.0f;
		PlayLayer::onQuit();
	}
	void startGame() {
		m_fields->performHideTwoPlayerGuide = false;
		PlayLayer::startGame();
	}
};