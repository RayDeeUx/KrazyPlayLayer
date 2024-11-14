#include <Geode/modify/PlayerObject.hpp>
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-2123456789)

class $modify(MyPlayerObject, PlayerObject) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("PlayerObject::playerDestroyed", PREFERRED_HOOK_PRIO);
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

		const auto fmod = FMODAudioEngine::sharedEngine();
		if (pl->m_isPlatformer) fmod->pauseAllMusic(true);
		else fmod->stopAllMusic(true);

		if (this == pl->m_player2 && pl->m_level->m_twoPlayerMode)
			return PlayerObject::playerDestroyed(p0);

		fmod->stopAllEffects(true);

		return PlayerObject::playerDestroyed(p0);
	}
};