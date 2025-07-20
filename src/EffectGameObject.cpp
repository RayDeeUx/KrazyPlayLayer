#include <Geode/modify/EffectGameObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)
#define ID_NOT_IN_VECTOR(id, theVector)\
	std::ranges::find(theVector, id) != theVector.end()

class $modify(MyEffectGameObject, EffectGameObject) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("EffectGameObject::triggerObject", PREFERRED_HOOK_PRIO);
	}
	struct Fields {
		const std::array<int, 2> sfxObjects = {3602, 3603};
		const std::array<int, 2> audioObjects = {1934, 3602};
	};
	void triggerObject(GJBaseGameLayer* p0, int p1, gd::vector<int> const* p2) {
		const Manager* manager = Manager::getSharedInstance();
		if (!manager->modEnabled)
			return EffectGameObject::triggerObject(p0, p1, p2);

		if (this->m_objectID == 1520 && manager->disableShakeTrigger) return;

		if (Utils::isEclipse())
			return EffectGameObject::triggerObject(p0, p1, p2);

		// for relevant comments on the source code below this line, please see:
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Level/MuteLevelSFX.cpp
		// https://raw.githubusercontent.com/EclipseMenu/EclipseMenu/main/src/hacks/Player/MuteLevelAudioOnDeath.cpp
		// reused with permission on grounds of self-authored code

		const PlayLayer* pl = PlayLayer::get();

		if (!pl) return EffectGameObject::triggerObject(p0, p1, p2);

		const PlayerObject* player = pl->m_player1;

		if (!player) return EffectGameObject::triggerObject(p0, p1, p2);

		if (manager->muteLevelOnDeath && player->m_isDead && ID_NOT_IN_VECTOR(this->m_objectID, m_fields->audioObjects)) return;

		if (manager->muteLevelSFX && ID_NOT_IN_VECTOR(this->m_objectID, m_fields->sfxObjects)) return;

		EffectGameObject::triggerObject(p0, p1, p2);
	}
};