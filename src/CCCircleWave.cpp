#include <Geode/modify/CCCircleWave.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

class $modify(MyCCCircleWave, CCCircleWave) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("CCCircleWave::setPosition", PREFERRED_HOOK_PRIO);
	}
	void setPosition(cocos2d::CCPoint const& p0) {
		CCCircleWave::setPosition(p0);

		const Manager* manager = Manager::getSharedInstance();
		if (!manager->modEnabled || !manager->hideLevelCompleteVFX || Utils::isEclipse()) return;

		// for relevant comments on the source code below this line, please see:
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Level/HideLevelCompleteVFX.cpp
		// reused with permission on grounds of self-authored code

		if (const PlayLayer* pl = PlayLayer::get(); !pl || !pl->m_levelEndAnimationStarted) return;
		
		if (!geode::cast::typeinfo_cast<CurrencyRewardLayer*>(this->getParent()))
			this->setVisible(false);
	}
};