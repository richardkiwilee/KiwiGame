class ModuleManager
{
public:
    ModuleManager(std::string path ) {
        path = path;
	};
    void Serialize(std::ofstream& ofs) {
    };
    void Deserialize(std::ifstream& ifs) {
    };
    void ApplyMods() {

	};
    void EnableMod(const std::string& mod_name) {
    }
    void DisableMod(const std::string& mod_name) {
	}
private:
    std::string path;
};
