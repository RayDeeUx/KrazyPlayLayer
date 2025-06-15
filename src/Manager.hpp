#pragma once
#include "Utils.hpp"

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:

	float endPortalX = 0.0f;
	float endPortalY = 0.0f;

	const std::vector<int> gravityPortals = {10, 11, 2926};
	const std::vector<int> particleObjects = {1586, 1700, 2065};
	const std::vector<int> teleportPortalObjects = {747, 749, 2064, 2902};
	const std::vector<int> jumpPadObjects = {35, 67, 140, 1332, 3005};
	const std::vector<int> speedPortalObjects = {200, 201, 202, 203, 1334};
	const std::vector<int> jumpRingObjects = {36, 84, 141, 1022, 1330, 1333, 3004};
	const std::vector<int> gameModePortals = {12, 13, 47, 111, 660, 745, 1331, 1933};
	const std::vector<int> collectibleObjects = {1275, 1587, 1589, 1598, 1614, 3601, 4401, 4402, 4403, 4404, 4405, 4406, 4407, 4408, 4409, 4410, 4411, 4412, 4413, 4414, 4415, 4416, 4417, 4418, 4419, 4420, 4421, 4422, 4423, 4424, 4425, 4426, 4427, 4428, 4429, 4430, 4431, 4432, 4433, 4434, 4435, 4436, 4437, 4438, 4439, 4440, 4441, 4442, 4443, 4444, 4445, 4446, 4447, 4448, 4449, 4450, 4451, 4452, 4453, 4454, 4455, 4456, 4457, 4458, 4459, 4460, 4461, 4462, 4463, 4464, 4465, 4466, 4467, 4468, 4469, 4470, 4471, 4472, 4473, 4474, 4475, 4476, 4477, 4478, 4479, 4480, 4481, 4482, 4483, 4484, 4485, 4486, 4487, 4488, 4489, 4490, 4491, 4492, 4493, 4494, 4495, 4496, 4497, 4498, 4499, 4500, 4501, 4502, 4503, 4504, 4505, 4506, 4507, 4508, 4509, 4510, 4511, 4512, 4513, 4514, 4515, 4516, 4517, 4518, 4519, 4520, 4521, 4522, 4523, 4524, 4525, 4526, 4527, 4528, 4529, 4530, 4531, 4532, 4533, 4534, 4535, 4536, 4539};
	const std::vector<int> everythingInOne = {10, 11, 12, 13, 35, 36, 45, 46, 47, 67, 84, 99, 101, 111, 140, 141, 142, 200, 201, 202, 203, 286, 287, 660, 745, 747, 749, 1022, 1275, 1329, 1330, 1331, 1332, 1333, 1334, 1586, 1587, 1589, 1594, 1598, 1614, 1700, 1704, 1751, 1933, 2064, 2065, 2902, 2926, 3004, 3005, 3601, 4401, 4402, 4403, 4404, 4405, 4406, 4407, 4408, 4409, 4410, 4411, 4412, 4413, 4414, 4415, 4416, 4417, 4418, 4419, 4420, 4421, 4422, 4423, 4424, 4425, 4426, 4427, 4428, 4429, 4430, 4431, 4432, 4433, 4434, 4435, 4436, 4437, 4438, 4439, 4440, 4441, 4442, 4443, 4444, 4445, 4446, 4447, 4448, 4449, 4450, 4451, 4452, 4453, 4454, 4455, 4456, 4457, 4458, 4459, 4460, 4461, 4462, 4463, 4464, 4465, 4466, 4467, 4468, 4469, 4470, 4471, 4472, 4473, 4474, 4475, 4476, 4477, 4478, 4479, 4480, 4481, 4482, 4483, 4484, 4485, 4486, 4487, 4488, 4489, 4490, 4491, 4492, 4493, 4494, 4495, 4496, 4497, 4498, 4499, 4500, 4501, 4502, 4503, 4504, 4505, 4506, 4507, 4508, 4509, 4510, 4511, 4512, 4513, 4514, 4515, 4516, 4517, 4518, 4519, 4520, 4521, 4522, 4523, 4524, 4525, 4526, 4527, 4528, 4529, 4530, 4531, 4532, 4533, 4534, 4535, 4536, 4539};

	std::string noSpiderEffects = "Disabled";
	std::string noEffects = "Ignore";

	bool modEnabled = false;

	bool disableShakeTrigger = false;

	bool hideLevelCompleteVFX = false;
	bool noEndPortalParticles = false;

	bool noPlayerParticles = false;
	bool noCubeGroundParticles = false;
	bool noBallGroundParticles = false;
	bool noRobotGroundParticles = false;
	bool noSpiderGroundParticles = false;
	bool noShipTrailingParticles = false;
	bool noUFOTrailingParticles = false;
	bool noSwingTrailingParticles = false;
	bool noShipClickParticles = false;
	bool noUFOClickParticles = false;
	bool noShipGroundParticles = false;
	bool noUFOGroundParticles = false;
	bool noWaveGroundParticles = false;
	bool noSwingGroundParticles = false;
	bool noRobotBurstParticles = false;
	bool noDashingParticles = false;
	bool noSwingBurstParticles = false;
	bool noLandingParticles = false;
	bool noDashFire = false;
	bool noRobotFire = false;
	bool noSwingFire = false;

	bool muteLevelOnDeath = false;
	bool muteRewardsSFX = false;
	bool muteLevelSFX = false;

	bool noGoldCoinParticles = false;
	bool noCoinParticles = false;
	bool noCustomOrbParticles = false;
	bool noTeleportOrbParticles = false;
	bool noDashOrbParticles = false;
	bool noDualPortalParticles = false;
	bool noMirrorPortalParticles = false;
	bool noSizePortalParticles = false;
	bool noJumpRingParticles = false;
	bool noJumpPadParticles = false;
	bool noGamemodePortalParticles = false;
	bool noSpeedPortalParticles = false;
	bool noGravityPortalParticles = false;
	bool noTeleportPortalParticles = false;
	bool noCollectibleParticles = false;
	bool noParticles = false;

	bool noSpeedParticles = false;

	static Manager* getSharedInstance() {
		if (!instance) instance = new Manager();
		return instance;
	}

	static void load() {
		if (!instance) instance = new Manager();
		instance->modEnabled = Utils::getBool("enabled");
		instance->noPlayerParticles = Utils::getBool("noPlayerParticles");
		instance->noCubeGroundParticles = Utils::getBool("noCubeGroundParticles");
		instance->noBallGroundParticles = Utils::getBool("noBallGroundParticles");
		instance->noRobotGroundParticles = Utils::getBool("noRobotGroundParticles");
		instance->noSpiderGroundParticles = Utils::getBool("noSpiderGroundParticles");
		instance->noShipTrailingParticles = Utils::getBool("noShipTrailingParticles");
		instance->noUFOTrailingParticles = Utils::getBool("noUFOTrailingParticles");
		instance->noSwingTrailingParticles = Utils::getBool("noSwingTrailingParticles");
		instance->noShipClickParticles = Utils::getBool("noShipClickParticles");
		instance->noUFOClickParticles = Utils::getBool("noUFOClickParticles");
		instance->noShipGroundParticles = Utils::getBool("noShipGroundParticles");
		instance->noUFOGroundParticles = Utils::getBool("noUFOGroundParticles");
		instance->noWaveGroundParticles = Utils::getBool("noWaveGroundParticles");
		instance->noSwingGroundParticles = Utils::getBool("noSwingGroundParticles");
		instance->noRobotBurstParticles = Utils::getBool("noRobotBurstParticles");
		instance->noDashingParticles = Utils::getBool("noDashingParticles");
		instance->noSwingBurstParticles = Utils::getBool("noSwingBurstParticles");
		instance->noLandingParticles = Utils::getBool("noLandingParticles");
		instance->noDashFire = Utils::getBool("noDashFire");
		instance->noRobotFire = Utils::getBool("noRobotFire");
		instance->noSwingFire = Utils::getBool("noSwingFire");
		instance->noGoldCoinParticles = Utils::getBool("noGoldCoinParticles");
		instance->noCoinParticles = Utils::getBool("noCoinParticles");
		instance->noCustomOrbParticles = Utils::getBool("noCustomOrbParticles");
		instance->noTeleportOrbParticles = Utils::getBool("noTeleportOrbParticles");
		instance->noDashOrbParticles = Utils::getBool("noDashOrbParticles");
		instance->noDualPortalParticles = Utils::getBool("noDualPortalParticles");
		instance->noMirrorPortalParticles = Utils::getBool("noMirrorPortalParticles");
		instance->noSizePortalParticles = Utils::getBool("noSizePortalParticles");
		instance->noJumpRingParticles = Utils::getBool("noJumpRingParticles");
		instance->noJumpPadParticles = Utils::getBool("noJumpPadParticles");
		instance->noGamemodePortalParticles = Utils::getBool("noGamemodePortalParticles");
		instance->noSpeedPortalParticles = Utils::getBool("noSpeedPortalParticles");
		instance->noGravityPortalParticles = Utils::getBool("noGravityPortalParticles");
		instance->noTeleportPortalParticles = Utils::getBool("noTeleportPortalParticles");
		instance->noCollectibleParticles = Utils::getBool("noCollectibleParticles");
		instance->noParticles = Utils::getBool("noParticles");
		instance->noSpeedParticles = Utils::getBool("noSpeedParticles");
		instance->noSpiderEffects = Utils::getString("noSpiderEffects");
		instance->muteLevelOnDeath = Utils::getBool("muteLevelOnDeath");
		instance->muteRewardsSFX = Utils::getBool("muteRewardsSFX");
		instance->muteLevelSFX = Utils::getBool("muteLevelSFX");
		instance->disableShakeTrigger = Utils::getBool("disableShakeTrigger");
		instance->noEffects = Utils::getString("noEffects");
		instance->hideLevelCompleteVFX = Utils::getBool("hideLevelCompleteVFX");
		instance->noEndPortalParticles = Utils::getBool("noEndPortalParticles");
	}
};