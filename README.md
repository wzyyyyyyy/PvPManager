# PvPManager
PvPManager
[![MSBuild](https://github.com/wzyyyyyyy/PvPManager/actions/workflows/msbuild.yml/badge.svg)](https://github.com/wzyyyyyyy/PvPManager/actions/workflows/msbuild.yml)

# 粒子特效设置教程

配置文件格式
```json
{
	"ParticleEffects":{
                //受伤时特效(仅玩家攻击玩家时触发)
		"onHurt": [
                        //如果想关闭粒子特效可以将此数组设置为空
			{
                                //粒子类型
				"ParticleEffectType":"minecraft:dust",
                                //偏移坐标，以玩家脚底的坐标为基准，例如玩家死亡的坐标是(0,0,0),则在(1,1,1)产生粒子效果，支持单精度浮点数
				"x":1,
				"y":1,
				"z":1
			},
                        //无限制，可以写很多粒子特效
			{
				"ParticleEffectType":"minecraft:evoker_spell",
				"x":0.5,
				"y":0.1,
				"z":0.9
			}
		],
                //死亡时特效(仅玩家击杀玩家时触发)，和上面的格式一样，也无限制粒子个数
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
```
