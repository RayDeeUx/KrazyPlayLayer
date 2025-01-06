#include <Geode/modify/CCCircleWave.hpp>
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

class $modify(MyCCCircleWave, CCCircleWave) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("CCCircleWave::setPosition", PREFERRED_HOOK_PRIO);
	}
	void setPosition(cocos2d::CCPoint const& p0) {
		CCCircleWave::setPosition(p0);

		if (!Utils::modEnabled() || !Utils::getBool("hideLevelCompleteVFX") || Utils::isEclipse()) return;

		// for relevant comments on the source code below this line, please see:
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Level/HideLevelCompleteVFX.cpp
		// reused with permission on grounds of self-authored code

		PlayLayer* pl = PlayLayer::get();

		if (!pl || !pl->m_levelEndAnimationStarted) return;
		
		if (!geode::cast::typeinfo_cast<CurrencyRewardLayer*>(this->getParent()))
			this->setVisible(false);
	}
};