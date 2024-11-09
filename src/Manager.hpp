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

	std::array<int, 3> gravityPortals = {10, 11, 2926};
	std::array<int, 3> particleObjects = {1586, 1700, 2065};
	std::array<int, 4> teleportPortalObjects = {747, 749, 2064, 2902};
	std::array<int, 5> jumpPadObjects = {35, 67, 140, 1332, 3005};
	std::array<int, 5> speedPortalObjects = {200, 201, 202, 203, 1334};
	std::array<int, 7> jumpRingObjects = {36, 84, 141, 1022, 1330, 1333, 3004};
	std::array<int, 8> gameModePortals = {12, 13, 47, 111, 660, 745, 1331, 1933};
	std::array<int, 143> collectibleObjects = {1275, 1587, 1589, 1598, 1614, 3601, 4401, 4402, 4403, 4404, 4405, 4406, 4407, 4408, 4409, 4410, 4411, 4412, 4413, 4414, 4415, 4416, 4417, 4418, 4419, 4420, 4421, 4422, 4423, 4424, 4425, 4426, 4427, 4428, 4429, 4430, 4431, 4432, 4433, 4434, 4435, 4436, 4437, 4438, 4439, 4440, 4441, 4442, 4443, 4444, 4445, 4446, 4447, 4448, 4449, 4450, 4451, 4452, 4453, 4454, 4455, 4456, 4457, 4458, 4459, 4460, 4461, 4462, 4463, 4464, 4465, 4466, 4467, 4468, 4469, 4470, 4471, 4472, 4473, 4474, 4475, 4476, 4477, 4478, 4479, 4480, 4481, 4482, 4483, 4484, 4485, 4486, 4487, 4488, 4489, 4490, 4491, 4492, 4493, 4494, 4495, 4496, 4497, 4498, 4499, 4500, 4501, 4502, 4503, 4504, 4505, 4506, 4507, 4508, 4509, 4510, 4511, 4512, 4513, 4514, 4515, 4516, 4517, 4518, 4519, 4520, 4521, 4522, 4523, 4524, 4525, 4526, 4527, 4528, 4529, 4530, 4531, 4532, 4533, 4534, 4535, 4536, 4539}; // 4405 to 4536 and then 4539

	static Manager* getSharedInstance() {
		if (!instance) {
			instance = new Manager();
		}
		return instance;
	}

};