#include <Geode/modify/PlayLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("PlayLayer::setupHasCompleted", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("PlayLayer::toggleGlitter", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("PlayLayer::postUpdate", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("PlayLayer::addObject", PREFERRED_HOOK_PRIO);
	}
	struct Fields {
		bool performHideTwoPlayerGuide = false;
		bool foundHitboxNodeTwoPlayerGuide = false;
		bool foundHitboxNode = false;
	};
	static bool isIn(const std::vector<int>& numberStorage, const int id) {
		return std::ranges::find(numberStorage, id) != numberStorage.end();
	}
	void addObject(GameObject* object) {
		if (!Utils::modEnabled()) return PlayLayer::addObject(object);
		if (const std::string& noGlow = Utils::getString("noGlow"); noGlow != "Ignore") {
			object->m_hasNoGlow = noGlow == "Force Enable"; // this has to go here because putting it in setupHasCompleted causes objects at camera's starting position to already have glow enabled
		}
		const Manager* manager = Manager::getSharedInstance();
		if (isIn(manager->particleObjects, object->m_objectID)) return PlayLayer::addObject(object);
		// truth be told, i could've done a switch case based on enum value. however, actual objects with noTouch property would be unaffected
		if (manager->noGoldCoinParticles && object->m_objectID == 142) object->m_hasParticles = false;
		else if (manager->noCoinParticles && object->m_objectID == 1329) object->m_hasNoParticles = true;
		else if (manager->noCustomOrbParticles && object->m_objectID == 1594) object->m_particleString = "";
		else if (manager->noTeleportOrbParticles && object->m_objectID == 3027) object->m_particleString = "";
		else if (manager->noDashOrbParticles && (object->m_objectID == 1704 || object->m_objectID == 1751)) object->m_particleString = "";
		else if (manager->noDualPortalParticles && (object->m_objectID == 286 || object->m_objectID == 287)) object->m_particleString = "";
		else if (manager->noMirrorPortalParticles && (object->m_objectID == 45 || object->m_objectID == 46)) object->m_particleString = "";
		else if (manager->noSizePortalParticles && (object->m_objectID == 99 || object->m_objectID == 101)) object->m_particleString = "";
		else if (manager->noJumpRingParticles && isIn(manager->jumpRingObjects, object->m_objectID)) object->m_particleString = "";
		else if (manager->noJumpPadParticles && isIn(manager->jumpPadObjects, object->m_objectID)) object->m_particleString = "";
		else if (manager->noGamemodePortalParticles && isIn(manager->gameModePortals, object->m_objectID)) object->m_particleString = "";
		else if (manager->noSpeedPortalParticles && isIn(manager->speedPortalObjects, object->m_objectID)) object->m_particleString = "";
		else if (manager->noGravityPortalParticles && isIn(manager->gravityPortals, object->m_objectID)) object->m_particleString = "";
		else if (manager->noTeleportPortalParticles && isIn(manager->teleportPortalObjects, object->m_objectID)) object->m_particleString = "";
		else if (manager->noCollectibleParticles && isIn(manager->collectibleObjects, object->m_objectID)) object->m_particleString = "";
		else if (manager->noParticles && !isIn(manager->everythingInOne, object->m_objectID)) object->m_particleString = "";
		PlayLayer::addObject(object);
	}
	void setupHasCompleted() {
		if (!Utils::modEnabled() || !m_objects || !m_level || !m_levelSettings) return PlayLayer::setupHasCompleted();
		if (!std::string(m_level->m_levelString).empty()) {
			const std::string& fixRobotJump = Utils::getString("fixRobotJump");
			const std::string& isFlipped = Utils::getString("isFlipped");
			const std::string& enable22Changes = Utils::getString("enable22Changes");
			const std::string& dynamicLevelHeight = Utils::getString("dynamicLevelHeight");
			const std::string& fixGravityBug = Utils::getString("fixGravityBug");
			const std::string& noTimePenalty = Utils::getString("noTimePenalty");
			if (fixRobotJump != "Ignore") {
				m_levelSettings->m_fixRobotJump = fixRobotJump == "Force Enable";
			}
			if (isFlipped != "Ignore") {
				m_levelSettings->m_isFlipped = isFlipped == "Force Enable";
			}
			if (enable22Changes != "Ignore") {
				m_levelSettings->m_enable22Changes = enable22Changes == "Force Enable";
			}
			if (dynamicLevelHeight != "Ignore") {
				m_levelSettings->m_dynamicLevelHeight = dynamicLevelHeight == "Force Enable";
			}
			if (fixGravityBug != "Ignore") {
				m_levelSettings->m_fixGravityBug = fixGravityBug == "Force Enable";
			}
			if (noTimePenalty != "Ignore" && m_level->isPlatformer()) {
				m_levelSettings->m_noTimePenalty = noTimePenalty == "Force Enable";
			}
		}
		PlayLayer::setupHasCompleted();
		const std::string& dontEnter = Utils::getString("dontEnter");
		const std::string& dontFade = Utils::getString("dontFade");
		const std::string& noAudioScale = Utils::getString("noAudioScale");
		const std::string& noEffects = Utils::getString("noEffects");
		for (GameObject* object : CCArrayExt<GameObject*>(m_objects)) {
			if (dontEnter != "Ignore") {
				object->m_ignoreEnter = dontEnter == "Force Enable";
			}
			if (dontFade != "Ignore") {
				object->m_ignoreFade = dontFade == "Force Enable";
			}
			if (noAudioScale != "Ignore") {
				object->m_hasNoAudioScale = noAudioScale == "Force Enable";
			}
			if (noEffects != "Ignore") {
				//
				// "Force Disable": force all objects to object->m_hasNoEffects = false regardless of invis status
				// "Force Enable": force all objects to object->m_hasNoEffects = true regardless of invis status
				// "Force Disable (+ Ignore Invis.)": force an object to object->m_hasNoEffects = false if object is visible
				// "Force Enable (+ Ignore Invis.)": force an object to object->m_hasNoEffects = true if object is visible
				// "Enable on Visible, Disable on Invis."
				// "Disable on Visible, Enable on Invis."

				// note: this could be optimized, but i wanted it to be readable source code.
				//
				if (noEffects == "Enable on Visible, Disable on Invis.") {
					object->m_hasNoEffects = !object->m_isHide && !object->m_isInvisible && object->getOpacity() > 0;
				} else if (noEffects == "Disable on Visible, Enable on Invis.") {
					object->m_hasNoEffects = !(!object->m_isHide && !object->m_isInvisible && object->getOpacity() > 0);
				} else if (utils::string::endsWith(noEffects, " (+ Ignore Invis.)")) {
					// if "(+ Ignore Invis.)" is found at the end, need to perform invis check
					bool isInvis = object->m_isHide || object->m_isInvisible || object->getOpacity() <= 0;
					if (!isInvis) object->m_hasNoEffects = utils::string::startsWith(noEffects, "Force Enable ");
				} else {
					// brute force override
					object->m_hasNoEffects = noEffects == "Force Enable";
				}
			}
		}
		if (m_level->m_twoPlayerMode && Utils::getBool("hideTwoPlayer")) m_fields->performHideTwoPlayerGuide = true;
	}
	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		const Manager* manager = Manager::getSharedInstance();
		if (!manager->modEnabled) return;
		const auto fields = m_fields.self();
		if (manager->noSpeedParticles && this->getChildren()) {
			for (CCNode* node : CCArrayExt<CCNode*>(this->getChildren())) {
				if (!fields->foundHitboxNode) fields->foundHitboxNode = !node->getID().empty() && node->getID() == "hitbox-node";
				if (!fields->foundHitboxNode || node->getZOrder() != 100) continue;
				if (const auto particle = typeinfo_cast<CCParticleSystemQuad*>(node)) particle->setVisible(false); // more than one particlesystem exists
			}
		}
		if (!fields->performHideTwoPlayerGuide) return;
		if (Utils::getBool("hideTwoPlayer")) {
			/*
			"omg ery why don't you hook PlayLayer::showTwoPlayerGuide()!! bad geode mod dev!"
			simple: refusing to call the original will cause more issues beyond intended
			also no bindings addresses!!
			*/
			for (CCNode* node : CCArrayExt<CCNode*>(getChildren())) {
				if (!fields->foundHitboxNodeTwoPlayerGuide) fields->foundHitboxNodeTwoPlayerGuide = node->getID() == "hitbox-node";
				if (!fields->foundHitboxNodeTwoPlayerGuide) continue;
				if (const auto text = typeinfo_cast<CCLabelBMFont*>(node)) {
					if (const auto &labelString = static_cast<const std::string&>(text->getString()); labelString != "Player 1" && labelString != "Player 2") continue;
					text->setVisible(false);
					text->setScale(0.0f);
					text->setContentHeight(0.0f);
					text->setContentWidth(0.0f);
					text->setColor({0,0,0});
					text->setOpacity(0);
					text->setZOrder(-3999);
					text->setString("");
					text->setPositionX(PREFERRED_HOOK_PRIO);
					text->setPositionY(PREFERRED_HOOK_PRIO);
				} else if (const auto sprite = typeinfo_cast<CCSprite*>(node)) {
					if (typeinfo_cast<CCLabelBMFont*>(sprite)) continue;
					if (cocos::isSpriteFrameName(sprite, "floorLine_001.png")) sprite->setVisible(false);
					fields->foundHitboxNodeTwoPlayerGuide = false;
					break;
				}
			}
		}
	}
	void toggleGlitter(bool p0) {
		if (Utils::getBool("noParticlesWhenFlying") && Utils::modEnabled()) p0 = false;
		return PlayLayer::toggleGlitter(p0);
	}
	void showCompleteEffect() {
		Manager* manager = Manager::getSharedInstance();
		if (!Utils::modEnabled() || !manager->noEndScreenShake || m_isPracticeMode) return PlayLayer::showCompleteEffect();
		manager->isInShowComplete = true;
		PlayLayer::showCompleteEffect();
		manager->isInShowComplete = false;
	}
	void resetLevel() {
		PlayLayer::resetLevel();
		if (!Utils::modEnabled()) return;
		Manager* manager = Manager::getSharedInstance();
		manager->isInShowComplete = false;
		if (!m_level) return;
		const std::string& alwaysFreezeCamera = Utils::getString("alwaysFreezeCameraAsIfItWereFirstAttempt");
		if (alwaysFreezeCamera == "Ignore") return;
		if (alwaysFreezeCamera == "All Levels") {
			m_freezeStartCamera = true;
			return;
		}
		const GJLevelType type = m_level->m_levelType;
		if (type == GJLevelType::Editor && alwaysFreezeCamera == "Editor Levels Only") {
			m_freezeStartCamera = true;
		} else if (type == GJLevelType::Saved && alwaysFreezeCamera == "Online Levels Only") {
			m_freezeStartCamera = true;
		} else if (type == GJLevelType::Local && alwaysFreezeCamera == "Main Levels Only") {
			m_freezeStartCamera = true;
		}
	}
	void onQuit() {
		Manager* manager = Manager::getSharedInstance();
		const auto fields = m_fields.self();
		fields->performHideTwoPlayerGuide = false;
		fields->foundHitboxNodeTwoPlayerGuide = false;
		fields->foundHitboxNode = false;
		manager->endPortalX = 0.0f;
		manager->endPortalY = 0.0f;
		manager->isInShowComplete = false;
		PlayLayer::onQuit();
	}
	void startGame() {
		m_fields->performHideTwoPlayerGuide = false;
		PlayLayer::startGame();
	}
};