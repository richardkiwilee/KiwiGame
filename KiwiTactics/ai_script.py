import character_module

def run_ai():
    # 创建一个角色实例
    player = character_module.Character()
    
    # 控制角色移动
    player.move(5, 10)
    print(player.get_position())

    # 角色执行攻击
    player.attack()

# 调用 AI 控制逻辑
run_ai()
