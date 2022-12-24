# PvPManager
PvPManager

# 粒子特效设置教程

配置文件格式
'''json
{
	"ParticleEffects":{
		"onHurt": [
			{
				"ParticleEffectType":"minecraft:dust",
				"x":1,
				"y":1,
				"z":1
			},
			{
				"ParticleEffectType":"minecraft:evoker_spell",
				"x":0.5,
				"y":0.1,
				"z":0.9
			}
		],
		"onDie": [
			{
				"ParticleEffectType":"minecraft:evoker_spell",
				"x":1,
				"y":1,
				"z":1
			}
		]
	}
}
'''
