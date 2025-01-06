#include <Geode/modify/CCParticleSystem.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-4000)

using namespace geode::prelude;

class $modify(MyCCParticleSystem, CCParticleSystem) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("CCParticleSystem::initParticle", PREFERRED_HOOK_PRIO);
	}
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	void initParticle(cocos2d::sCCParticle* p0) {
		CCParticleSystem::initParticle(p0);
		if (!Utils::modEnabled() || !typeinfo_cast<cocos2d::CCParticleSystemQuad*>(this)) return;
		auto pl = PlayLayer::get();
		auto parent = this->getParent();
		if (!pl || !parent) return;
		if (Utils::getBool("hideLevelCompleteVFX") && !Utils::isEclipse()) {
			// for relevant comments on the source code within this conditional statement, please see:
			// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Level/HideLevelCompleteVFX.cpp
			// reused with permission on grounds of self-authored code
			if (parent == pl && pl->m_levelEndAnimationStarted) this->setVisible(false);
		}
		if (Utils::getBool("noEndPortalParticles")) {
			if (pl->m_level->isPlatformer() || !typeinfo_cast<CCLayer*>(parent)) return;
			if (this->getTag() != 4 || parent->getID() != "batch-layer") return;
			if (m_fields->manager->endPortalX - 15 != this->getPositionX() || m_fields->manager->endPortalY != this->getPositionY()) return;
			this->setVisible(false);
		}
	}
};