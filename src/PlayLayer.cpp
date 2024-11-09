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
		std::array<int, 3> particleObjects = {1586, 1700, 2065};
		std::vector<int> speedPortalObjects = {200, 201, 202, 203, 1334};
	};
	void addObject(GameObject* object) {
		if (!Utils::modEnabled()) return PlayLayer::addObject(object);
		if (std::ranges::find(m_fields->particleObjects, object->m_objectID) == m_fields->particleObjects.end()) {
			if (object->m_objectID == 142 && Utils::getBool("noGoldCoinParticles")) object->m_hasParticles = false;
			else if (object->m_objectID == 1329 && Utils::getBool("noCoinParticles")) object->m_hasNoParticles = true;
			else if (Utils::getBool("noObjectParticles") && object->m_objectID != 142 && object->m_objectID != 1329) {
				object->m_particleString = "";
			} else {
				switch (object->m_objectType) {
					case GameObjectType::YellowJumpRing: if (Utils::getBool("noJumpRingParticles")) object->m_particleString = "";
					case GameObjectType::RedJumpRing: if (Utils::getBool("noJumpRingParticles")) object->m_particleString = "";
					case GameObjectType::PinkJumpRing: if (Utils::getBool("noJumpRingParticles")) object->m_particleString = "";
					case GameObjectType::GravityRing: if (Utils::getBool("noJumpRingParticles")) object->m_particleString = "";
					case GameObjectType::DropRing: if (Utils::getBool("noJumpRingParticles")) object->m_particleString = "";
					case GameObjectType::GreenRing: if (Utils::getBool("noJumpRingParticles")) object->m_particleString = "";

					case GameObjectType::DashRing: if (Utils::getBool("noDashOrbParticles")) object->m_particleString = "";
					case GameObjectType::GravityDashRing: if (Utils::getBool("noDashOrbParticles")) object->m_particleString = "";

					case GameObjectType::CustomRing: if (Utils::getBool("noCustomOrbParticles")) object->m_particleString = "";

					case GameObjectType::TeleportOrb: if (Utils::getBool("noTeleportOrbParticles")) object->m_particleString = "";

					case GameObjectType::GravityPad: if (Utils::getBool("noJumpPadParticles")) object->m_particleString = "";
					case GameObjectType::SpiderPad: if (Utils::getBool("noJumpPadParticles")) object->m_particleString = "";
					case GameObjectType::PinkJumpPad: if (Utils::getBool("noJumpPadParticles")) object->m_particleString = "";
					case GameObjectType::RedJumpPad: if (Utils::getBool("noJumpPadParticles")) object->m_particleString = "";
					case GameObjectType::YellowJumpPad: if (Utils::getBool("noJumpPadParticles")) object->m_particleString = "";

					case GameObjectType::CubePortal: if (Utils::getBool("noGamemodePortalParticles")) object->m_particleString = "";
					case GameObjectType::ShipPortal: if (Utils::getBool("noGamemodePortalParticles")) object->m_particleString = "";
					case GameObjectType::BallPortal: if (Utils::getBool("noGamemodePortalParticles")) object->m_particleString = "";
					case GameObjectType::UfoPortal: if (Utils::getBool("noGamemodePortalParticles")) object->m_particleString = "";
					case GameObjectType::WavePortal: if (Utils::getBool("noGamemodePortalParticles")) object->m_particleString = "";
					case GameObjectType::RobotPortal: if (Utils::getBool("noGamemodePortalParticles")) object->m_particleString = "";
					case GameObjectType::SwingPortal: if (Utils::getBool("noGamemodePortalParticles")) object->m_particleString = "";

					case GameObjectType::DualPortal: if (Utils::getBool("noDualPortalParticles")) object->m_particleString = "";
					case GameObjectType::SoloPortal: if (Utils::getBool("noDualPortalParticles")) object->m_particleString = "";

					case GameObjectType::InverseMirrorPortal: if (Utils::getBool("noMirrorPortalParticles")) object->m_particleString = "";
					case GameObjectType::NormalMirrorPortal: if (Utils::getBool("noMirrorPortalParticles")) object->m_particleString = "";

					case GameObjectType::GravityTogglePortal: if (Utils::getBool("noGravityPortalParticles")) object->m_particleString = "";
					case GameObjectType::InverseGravityPortal: if (Utils::getBool("noGravityPortalParticles")) object->m_particleString = "";
					case GameObjectType::NormalGravityPortal: if (Utils::getBool("noGravityPortalParticles")) object->m_particleString = "";

					case GameObjectType::MiniSizePortal: if (Utils::getBool("noSizePortalParticles")) object->m_particleString = "";
					case GameObjectType::RegularSizePortal: if (Utils::getBool("noSizePortalParticles")) object->m_particleString = "";

					case GameObjectType::TeleportPortal: if (Utils::getBool("noTeleportPortalParticles")) object->m_particleString = "";

					case GameObjectType::Collectible: if (Utils::getBool("noCollectibleParticles")) object->m_particleString = "";

					case GameObjectType::Modifier: if (Utils::getBool("noSpeedPortalParticles") && std::ranges::find(m_fields->speedPortalObjects, object->m_objectID) != m_fields->speedPortalObjects.end()) object->m_particleString = "";

					default: if (Utils::getBool("noParticles")) object->m_particleString = "";
				}
			}
		}
		if (const std::string& noGlow = Utils::getString("noGlow"); noGlow != "Ignore") {
			object->m_hasNoGlow = noGlow == "Force Enable"; // this has to go here because putting it in setupHasCompleted causes objects at camera's starting position to already have glow enabled
		}
		PlayLayer::addObject(object);
	}
	void setupHasCompleted() {
		PlayLayer::setupHasCompleted();
		if (!Utils::modEnabled()) return;
		if (m_objects) for (const auto &object : CCArrayExt<GameObject*>(m_objects)) {
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
		if (!m_level || !m_levelSettings) return;
		if (m_level->m_twoPlayerMode && Utils::getBool("hideTwoPlayer")) m_fields->performHideTwoPlayerGuide = true;
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
	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		if (!Utils::modEnabled()) return;
		if (Utils::getBool("noSpeedParticles")) {
			for (const auto &node : CCArrayExt<CCNode*>(getChildren())) {
				if (!m_fields->foundHitboxNode) m_fields->foundHitboxNode = node->getID() == "hitbox-node";
				if (!m_fields->foundHitboxNode || node->getZOrder() != 100) continue;
				if (const auto particle = typeinfo_cast<CCParticleSystemQuad*>(node)) particle->setVisible(false);
			}
		}
		if (auto batch = getChildByIDRecursive("batch-layer"); Utils::getBool("noPlayerParticles")) {
			for (const auto &node : CCArrayExt<CCNode*>(batch->getChildren())) {
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