import os
import ai_module

print(os.sys.path)
print(dir())
print(dir(ai_module))
print(dir(ai_module.AIModel))

# 修改 C++ 中的 model.a
ai_module.AIModel.a = 42
print(ai_module.AIModel.a)