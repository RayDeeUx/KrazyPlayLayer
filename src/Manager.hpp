#pragma once

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:

	float endPortalX = 0.0f;
	float endPortalY = 0.0f;

	std::array<int, 3> particleObjects = {1586, 1700, 2065};
	std::vector<int> teleportPortalObjects = {2064, 2902, 749, 747};
	std::vector<int> speedPortalObjects = {200, 201, 202, 203, 1334};
	std::vector<int> jumpRingObjects = {36, 1333, 141, 84, 1330, 1022, 3004};
	std::vector<int> jumpPadObjects = {67, 3005, 140, 1332, 35};
	std::vector<int> gameModePortals = {12, 13, 47, 111, 660, 745, 1331, 1933};
	std::vector<int> gravityPortals = {10, 11, 2926};

	static Manager* getSharedInstance() {
		if (!instance) {
			instance = new Manager();
		}
		return instance;
	}

};