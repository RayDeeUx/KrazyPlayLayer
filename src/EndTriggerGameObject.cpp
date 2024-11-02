#include <Geode/modify/EndTriggerGameObject.hpp>
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-2123456789)

using namespace geode::prelude;

class $modify(MyEndTriggerGameObject, EndTriggerGameObject) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("EndTriggerGameObject::triggerObject", PREFERRED_HOOK_PRIO);
	}
	void triggerObject(GJBaseGameLayer *p0, int p1, gd::vector<int> const *p2) {
		if (!Utils::modEnabled()) return EndTriggerGameObject::triggerObject(p0, p1, p2);
		const auto pl = PlayLayer::get();
		if (!pl) return;
		const auto level = pl->m_level;
		if (!level) return;
		const std::string& settingsSuffix = level->isPlatformer() ? "Plat" : "Classic";
		if (const std::string& endPortalNoSFX = Utils::getString(fmt::format("endPortalNoSFX{}", settingsSuffix)); endPortalNoSFX != "Ignore") {
			this->m_noSFX = endPortalNoSFX == "Force Enable";
		}
		if (const std::string& endPortalInstant = Utils::getString(fmt::format("endPortalInstant{}", settingsSuffix)); endPortalInstant != "Ignore") {
			this->m_instant = endPortalInstant == "Force Enable";
		}
		if (const std::string& endPortalNoEffects = Utils::getString(fmt::format("endPortalNoEffects{}", settingsSuffix)); endPortalNoEffects != "Ignore") {
			this->m_noEffects = endPortalNoEffects == "Force Enable";
		}
		EndTriggerGameObject::triggerObject(p0, p1, p2);
	}
};