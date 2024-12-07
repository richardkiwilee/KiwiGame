function print_table(t, indent)
    -- 设置默认的缩进
    if not indent then indent = 0 end
    
    -- 处理是否为表格
    if type(t) == "table" then
        for k, v in pairs(t) do
            -- 输出键
            local key_str = "[" .. tostring(k) .. "]"
            
            -- 输出缩进
            local indentation = string.rep("  ", indent)
            if type(v) == "table" then
                -- 如果值是表格，则递归打印
                print(indentation .. key_str .. " = {")
                print_table(v, indent + 1)  -- 递归
                print(indentation .. "}")
            else
                -- 否则直接输出值
                print(indentation .. key_str .. " = " .. tostring(v))
            end
        end
    else
        -- 直接打印其他类型的数据
        print(string.rep("  ", indent) .. tostring(t))
    end
end

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
