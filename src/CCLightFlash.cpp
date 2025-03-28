#include <Geode/modify/CCLightFlash.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

class $modify(MyCCLightFlash, CCLightFlash) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("CCLightFlash::playEffect", PREFERRED_HOOK_PRIO);
	}
	void playEffect(cocos2d::CCPoint point, cocos2d::ccColor3B color, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, float p15, int p16, bool p17, bool p18, float p19) {
		CCLightFlash::playEffect(
			point, color, p2, p3, p4, p5, p6, p7, p8, p9, p10,
			p11, p12, p13, p14, p15, p16, p17, p18, p19
		);

		const Manager* manager = Manager::getSharedInstance();
		if (!manager->modEnabled || !manager->hideLevelCompleteVFX || Utils::isEclipse()) return;

		// for relevant comments on the source code below this line, please see:
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Level/HideLevelCompleteVFX.cpp
		// reused with permission on grounds of self-authored code

		if (const PlayLayer* pl = PlayLayer::get(); !pl || !pl->m_levelEndAnimationStarted) return;

		this->setVisible(false);
	}
};