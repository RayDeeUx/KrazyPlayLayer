#include <Geode/modify/PlayerObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

#define HIDE(item)\
	item->setVisible(false);\
	item->setOpacity(0);\
	item->setScale(0);

#define PASSIVE_HIDE(item) item->setVisible(false);
#define PASSIVE_VISIBLE(item) item->setVisible(true);

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
			HIDE(dashFire)
			if (CCSprite* child = dashFire->getChildByType<CCSprite>(0)) {
				HIDE(child)
			}
		}
		if (PlayerFireBoostSprite* robotFire = this->m_robotFire; robotFire && manager->noRobotFire) {
			HIDE(robotFire)
		}
		if (manager->noSwingFire) {
			if (PlayerFireBoostSprite* swingTop = this->m_swingFireTop) {
				HIDE(swingTop)
			}
			if (PlayerFireBoostSprite* swingMiddle = this->m_swingFireMiddle) {
				HIDE(swingMiddle)
			}
			if (PlayerFireBoostSprite* swingBottom = this->m_swingFireBottom) {
				HIDE(swingBottom)
			}
		}
		const GameManager* gm = GameManager::get();
		if (m_playerGroundParticles) {
			if (!this->m_isShip && !this->m_isBall && !this->m_isBird && !this->m_isDart && !this->m_isRobot && !this->m_isSpider && !this->m_isSwing && manager->noCubeGroundParticles) {
				PASSIVE_HIDE(m_playerGroundParticles)
			} else if ((this->m_isBall && manager->noBallGroundParticles) || (this->m_isRobot && manager->noRobotGroundParticles) || (this->m_isSpider && manager->noSpiderGroundParticles)) {
				PASSIVE_HIDE(m_playerGroundParticles)
			} else if (!gm->m_performanceMode) PASSIVE_VISIBLE(m_playerGroundParticles)
		}
		if (m_trailingParticles) {
			if ((this->m_isShip && manager->noShipTrailingParticles) || (this->m_isBird && manager->noUFOTrailingParticles) || (this->m_isSwing && manager->noSwingTrailingParticles)) {
				PASSIVE_HIDE(m_trailingParticles)
			} else if (!gm->m_performanceMode) PASSIVE_VISIBLE(m_trailingParticles)
		}
		if (manager->noShipClickParticles && m_shipClickParticles) {
			PASSIVE_HIDE(m_shipClickParticles)
		}
		if (manager->noUFOClickParticles && m_ufoClickParticles) {
			PASSIVE_HIDE(m_ufoClickParticles)
		}
		if (m_vehicleGroundParticles) {
			if ((this->m_isShip && manager->noShipGroundParticles) || (this->m_isBird && manager->noUFOGroundParticles) || (this->m_isSwing && manager->noSwingGroundParticles) || (this->m_isDart && manager->noWaveGroundParticles)) {
				PASSIVE_HIDE(m_vehicleGroundParticles)
			} else if (!gm->m_performanceMode) PASSIVE_VISIBLE(m_vehicleGroundParticles)
		}
		if (manager->noRobotBurstParticles && m_robotBurstParticles) {
			PASSIVE_HIDE(m_robotBurstParticles)
		}
		if (manager->noDashingParticles && m_dashParticles) {
			PASSIVE_HIDE(m_dashParticles)
		}
		if (manager->noSwingBurstParticles) {
			if (m_swingBurstParticles1) {
				PASSIVE_HIDE(m_swingBurstParticles1)
			}
			if (m_swingBurstParticles2) {
				PASSIVE_HIDE(m_swingBurstParticles2)
			}
		}
		if (manager->noLandingParticles) {
			if (m_landParticles0) {
				PASSIVE_HIDE(m_landParticles0)
			}
			if (m_landParticles1) {
				PASSIVE_HIDE(m_landParticles1)
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