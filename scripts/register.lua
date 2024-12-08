function WaterBall(info)
    print_table(info)
    -- 获取 Attacker 表
    local attacker = info["Attacker"]
    
    -- 检查 attacker 是否为 nil
    if attacker == nil then
        print("Error: Attacker is nil!")
        return 0  -- 或者返回一个默认值
    end
    
    -- 检查 Armor 是否存在
    local armor = attacker["Armor"]
    if armor == nil then
        print("Error: Armor is nil in Attacker!")
        return 0  -- 或者返回一个默认值
    end
    
    -- 返回 Attacker.Armor * 30 + 50
    return armor * 30 + 50
end
