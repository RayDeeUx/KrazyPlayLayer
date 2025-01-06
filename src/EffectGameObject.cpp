#include <Geode/modify/EffectGameObject.hpp>
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-4000)

class $modify(MyEffectGameObject, EffectGameObject) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("EffectGameObject::triggerObject", PREFERRED_HOOK_PRIO);
	}
	struct Fields {
		std::array<int, 2> sfxObjects = {3602, 3603};
		std::array<int, 2> audioObjects = {1934, 3602};
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		if (!Utils::modEnabled() || Utils::isEclipse())
			return EffectGameObject::triggerObject(p0, p1, p2);

		// for relevant comments on the source code below this line, please see:
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Level/MuteLevelSFX.cpp
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Player/MuteLevelAudioOnDeath.cpp
		// reused with permission on grounds of self-authored code

		PlayLayer* pl = PlayLayer::get();

		if (!pl) return EffectGameObject::triggerObject(p0, p1, p2);

		PlayerObject* player = pl->m_player1;

		if (!player) return EffectGameObject::triggerObject(p0, p1, p2);

		if (Utils::getBool("muteLevelOnDeath") && player->m_isDead && std::ranges::find(m_fields->audioObjects, this->m_objectID) != m_fields->audioObjects.end()) return;

		if (Utils::getBool("muteLevelSFX") && std::ranges::find(m_fields->sfxObjects, this->m_objectID) != m_fields->sfxObjects.end()) return;

		EffectGameObject::triggerObject(p0, p1, p2);
	}
};