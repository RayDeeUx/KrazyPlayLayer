#include <Geode/modify/PlayerObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

#define HIDE_FIRE(sprite)\
	sprite->setVisible(false);\
	sprite->setOpacity(0);\
	sprite->setScale(0);\

class $modify(MyPlayerObject, PlayerObject) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("PlayerObject::playSpiderDashEffect", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("PlayerObject::playerDestroyed", PREFERRED_HOOK_PRIO);
		(void) self.setHookPriority("PlayerObject::update", PREFERRED_HOOK_PRIO);
	}
	void playerDestroyed(bool p0) {
		if (!Utils::modEnabled() || !Utils::getBool("muteLevelOnDeath") || Utils::isEclipse())
			return PlayerObject::playerDestroyed(p0);

		// for relevant comments on the source code below this line, please see:
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Player/MuteLevelAudioOnDeath.cpp
		// reused with permission on grounds of self-authored code

		PlayLayer* pl = PlayLayer::get();

		if (!pl) return PlayerObject::playerDestroyed(p0);

		if (this != pl->m_player1 && this != pl->m_player2)
			return PlayerObject::playerDestroyed(p0);

		if (pl->m_isPracticeMode && !pl->m_practiceMusicSync)
			return PlayerObject::playerDestroyed(p0);

		auto fmod = FMODAudioEngine::sharedEngine();
		if (pl->m_isPlatformer) fmod->pauseAllMusic(true);
		else fmod->stopAllMusic(true);

		if (this == pl->m_player2 && pl->m_level->m_twoPlayerMode)
			return PlayerObject::playerDestroyed(p0);

		fmod->stopAllEffects();

		return PlayerObject::playerDestroyed(p0);
	}
	void update(float dt) {
		PlayerObject::update(dt);
		const Manager* manager = Manager::getSharedInstance();
		if (!manager->modEnabled) return;
		const PlayLayer* pl = PlayLayer::get();
		if (!pl) return;
		if (this != pl->m_player1 && this != pl->m_player2) return;
		if (CCSprite* dashFire = this->m_dashFireSprite; dashFire && manager->noDashFire && this->m_isDashing) {
			HIDE_FIRE(dashFire)
			if (CCSprite* child = dashFire->getChildByType<CCSprite>(0)) {
				HIDE_FIRE(child)
			}
		}
		if (PlayerFireBoostSprite* robotFire = this->m_robotFire; robotFire && manager->noRobotFire) {
			HIDE_FIRE(robotFire)
		}
		if (manager->noSwingFire) {
			if (PlayerFireBoostSprite* swingTop = this->m_swingFireTop) {
				HIDE_FIRE(swingTop)
			}
			if (PlayerFireBoostSprite* swingMiddle = this->m_swingFireMiddle) {
				HIDE_FIRE(swingMiddle)
			}
			if (PlayerFireBoostSprite* swingBottom = this->m_swingFireBottom) {
				HIDE_FIRE(swingBottom)
			}
		}
	}
	void playSpiderDashEffect(CCPoint from, CCPoint to) {
		const Manager* manager = Manager::getSharedInstance();
		if (!manager->modEnabled) return PlayerObject::playSpiderDashEffect(from, to);
		if (const PlayLayer* pl = PlayLayer::get(); !pl || (this != pl->m_player1 && this != pl->m_player2)) return PlayerObject::playSpiderDashEffect(from, to);
		if (manager->noSpiderEffects == "Spider Mode + Pad + Orbs") return;
		if (manager->noSpiderEffects == "Spider Mode Only" && this->m_isSpider) return;
		PlayerObject::playSpiderDashEffect(from, to);
	}
};