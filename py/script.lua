-- script.lua
print("Before modification: " .. model.a)

-- 修改 C++ 对象成员变量 a
model.a = 42

print("After modification: " .. model.a)
