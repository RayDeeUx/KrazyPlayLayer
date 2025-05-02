#include <Geode/modify/FMODAudioEngine.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

using namespace geode::prelude;

class $modify(MuteRewardsSFXFMODAEHook, FMODAudioEngine) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("FMODAudioEngine::playEffect", PREFERRED_HOOK_PRIO);
	}
	struct Fields {
		const std::array<std::string_view, 4> badSFX = { "achievement_01.ogg", "magicExplosion.ogg", "gold02.ogg", "secretKey.ogg" };
	};
	int playEffect(gd::string path, float speed, float p2, float volume) {
		const Manager* manager = Manager::getSharedInstance();
		if (!manager->modEnabled || !manager->muteRewardsSFX || Utils::isEclipse())
			return FMODAudioEngine::playEffect(path, speed, p2, volume);

		// for relevant comments on the source code below this line, please see:
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Player/MuteLevelAudioOnDeath.cpp
		// reused with permission on grounds of self-authored code

		const PlayLayer* pl = PlayLayer::get();

		if (!pl || !pl->m_player1->m_isDead || pl->m_isPaused)
			return FMODAudioEngine::playEffect(path, speed, p2, volume);

		if (std::ranges::find(m_fields->badSFX, std::string_view(path)) == m_fields->badSFX.end())
			return FMODAudioEngine::playEffect(path, speed, p2, volume);

		return 0;
	}
};