#include <Geode/modify/EndTriggerGameObject.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define PREFERRED_HOOK_PRIO (-3999)

using namespace geode::prelude;

class $modify(MyEndTriggerGameObject, EndTriggerGameObject) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("EndTriggerGameObject::customObjectSetup", PREFERRED_HOOK_PRIO);
	}
	void customObjectSetup(gd::vector<gd::string>& p0, gd::vector<void*>& p1) {
		EndTriggerGameObject::customObjectSetup(p0, p1);
		if (!Manager::getSharedInstance()->modEnabled) return;
		const PlayLayer* pl = PlayLayer::get();
		if (!pl) return;
		GJGameLevel* level = pl->m_level;
		if (!level) return;
		const std::string& settingsSuffix = level->isPlatformer() ? "Plat" : "Classic";
		const std::string& endPortalNoSFX = Utils::getString(fmt::format("endPortalNoSFX{}", settingsSuffix));
		const std::string& endPortalInstant = Utils::getString(fmt::format("endPortalInstant{}", settingsSuffix));
		const std::string& endPortalNoEffects = Utils::getString(fmt::format("endPortalNoEffects{}", settingsSuffix));
		if (endPortalNoSFX != "Ignore") {
			this->m_noSFX = endPortalNoSFX == "Force Enable";
		}
		if (endPortalInstant != "Ignore") {
			this->m_instant = endPortalInstant == "Force Enable";
		}
		if (endPortalNoEffects != "Ignore") {
			this->m_noEffects = endPortalNoEffects == "Force Enable";
		}
	}
};