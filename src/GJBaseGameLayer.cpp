#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Manager.hpp"

using namespace geode::prelude;

class $modify(MyGJBaseGameLayer, GJBaseGameLayer) {
	void shakeCamera(float duration, float strength, float interval) {
		if (LevelEditorLayer::get()) return GJBaseGameLayer::shakeCamera(duration, strength, interval);
		if (const Manager* manager = Manager::getSharedInstance(); !m_isPracticeMode && Utils::modEnabled() && manager->noEndScreenShake && manager->isInShowComplete) return;
		GJBaseGameLayer::shakeCamera(duration, strength, interval);
	}
};