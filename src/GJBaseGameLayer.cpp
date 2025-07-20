#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Manager.hpp"

using namespace geode::prelude;

class $modify(MyGJBaseGameLayer, GJBaseGameLayer) {
	void shakeCamera(float duration, float strength, float interval) {
		if (LevelEditorLayer::get() || !m_level) return GJBaseGameLayer::shakeCamera(duration, strength, interval);
		const PlayLayer* pl = PlayLayer::get();
		if (const Manager* manager = Manager::getSharedInstance(); !m_level->isPlatformer() && !m_isPracticeMode && Utils::modEnabled() && manager->noEndScreenShake && manager->isInShowComplete && pl->m_levelEndAnimationStarted) return;
		GJBaseGameLayer::shakeCamera(duration, strength, interval);
	}
};