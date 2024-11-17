// #include <Geode/modify/EndTriggerGameObject.hpp>
// #include <Geode/modify/GameObject.hpp>

// #include "Utils.hpp"

// #define PREFERRED_HOOK_PRIO (2123456789)

// using namespace geode::prelude;

// class $modify(MyGameObject, GameObject) {
// 	static void onModify(auto& self) {
// 		(void) self.setHookPriority("GameObject::activateObject", PREFERRED_HOOK_PRIO);
// 	}
// 	void activateObject() {
// 		if (!Utils::modEnabled() || LevelEditorLayer::get()) return this->activateObject();
// 		if (this->m_objectID == 1520 && Utils::getBool("disableShakeTrigger")) return;
// 		std::string noEffects = Utils::getString("noEffects");
// 		if (noEffects == "Ignore") return this->activateObject();
// 		if (noEffects == "Enable on Visible, Disable on Invis.") {
// 			this->m_hasNoEffects = !this->m_isHide && !this->m_isInvisible && this->getOpacity() > 0;
// 		} else if (noEffects == "Disable on Visible, Enable on Invis.") {
// 			this->m_hasNoEffects = !(!this->m_isHide && !this->m_isInvisible && this->getOpacity() > 0);
// 		} else if (utils::string::endsWith(noEffects, " (+ Ignore Invis.)")) {
// 			// if "(+ Ignore Invis.)" is found at the end, need to perform invis check
// 			bool isInvis = this->m_isHide || this->m_isInvisible || this->getOpacity() <= 0;
// 			if (!isInvis) this->m_hasNoEffects = utils::string::startsWith(noEffects, "Force Enable ");
// 		} else {
// 			// brute force override
// 			this->m_hasNoEffects = noEffects == "Force Enable";
// 		}
// 		this->activateObject();
// 	}
// };