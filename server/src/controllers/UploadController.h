#pragma once

#include <crow.h>
#include <string>
#include <memory>
#include <map>
#include <mutex>

namespace services {
	class TransferService;
}

class UploadController {
public:
	UploadController();
	~UploadController();

	bool initialize(std::shared_ptr<services::TransferService> transferService);

	crow::json::wvalue handleUpload			(const crow::request& req);
	crow::json::wvalue getProgress			(const std::string& uploadId);
	crow::json::wvalue getAllUploads();
	crow::json::wvalue getActiveUploads();
	crow::json::wvalue cancelUpload			(const std::string& uploadId);
	crow::json::wvalue pauseUpload			(const std::string& upladId);
	crow::json::wvalue resumeUpload			(const std::string& uploadId);
	crow::json::wvalue clearCompleted();
	crow::json::wvalue removeUpload			(const std::string& uploadId);
	crow::json::wvalue validateFile			(const crow::request& req);

private:
	std::shared_ptr<services::TransferService> transferService_;
	std::string tempUploadDir_;
	std::string pspIsoDir_;
	std::map<std::string, crow::websocket::connection*> wsConnections_;
	std::mutex wsMutex_;

	struct UploadedFile {
		std::string filename;
		std::string contentType;
		std::string tempPath;
		size_t size;
	};

	UploadedFile parseMultipartFormData(const crow::request& req);

	std::string saveTempFiles(const std::string& filename, const std::string& data);
	void cleanupTempFile(const std::string& path);
	void notifyProgress(const std::string& uploadId, const crow::json::wvalue& data);
	void createTempDirectory();
	void cleanupOldTempFiles();

	struct ValidationResult {
		bool isValid;
		std::string error;
		size_t fileSize;
	};

	ValidationResult validateUploadedFile(
		const UploadedFile& file
	);

	crow::json::wvalue createErrorResponce(const std::string& message);
	crow::json::wvalue createSuccessResponce(const std::string& message);
	crow::json::wvalue createSuccessResponce(const std::string& message);
	std::string generateUniqueFilename(const std::string& originalName);
};