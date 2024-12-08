#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Logger {
public:
    // ��ȡ����ʵ��
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    };

    // ��ֹ��������͸�ֵ������
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void Info(const std::string& msg) {
        console->info(msg);
        file_logger->info(msg);
    }

    void Warn(const std::string& msg) {
		console->warn(msg);
		file_logger->warn(msg);
	}

    void Error(const std::string& msg) {
        console->error(msg);
        file_logger->error(msg);
    }

    void Catch(const std::exception& e)
    {
        //try {
        //    throw std::runtime_error("An example exception");
        //}
        //catch (const std::exception& e) {
        //    spdlog::error("Caught an exception: {}", e.what());
        //}
        spdlog::error("Caught an exception: {}", e.what());
    }

private:
    // ˽�й��캯������������
    Logger()
    {
        console = spdlog::stdout_color_mt("console");
        console->set_level(spdlog::level::info); // ������־����
        console->set_pattern("[%Y-%m-%d %H:%M:%S] [%-5l] %v"); // ������־��ʽ
        file_logger = spdlog::basic_logger_mt("file_logger", "logs/example.log");
        file_logger->set_level(spdlog::level::debug); // �����ļ���־����
        file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); // ������־��ʽ
    };
    ~Logger() {};

    std::shared_ptr<spdlog::logger> console = nullptr;
    std::shared_ptr<spdlog::logger> file_logger = nullptr;

};

#endif
