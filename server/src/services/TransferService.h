#pragma once 

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <atomic>
#include <mutex>
#include <map>

class PSPDevice;
class FileTransfer;

struct TransferInfo {
	std::string id;
	std::string filename;
	std::string sourcePath;
	std::string destiantionPath;
	size_t fileSize;
	size_t bytesTransferred;
	double progress;
	double speed;
	std::string status;
	std::string error;
	long long startTime;
	long long endTime;
	long long estimatedCompletionTime;
};

using ProgressCallback = std::function<void(const TransferInfo&)>;

class TransferService {
public:
	TransferService();
	~TransferService();

	//Initialize the service with a PSP device
	bool initialize(std::shared_ptr<PSPDevice> device);

	std::string startTransfer(
		const std::string& sourcePath,
		const std::string& destinationPath,
		ProgressCallback callbacl = nullptr
	);

	TransferInfo getTransferInfo(const std::string& transferId);
	std::vector<TransferInfo> gertAllTransfers();
	std::vector<TransferInfo> getActiveTransfers();
	bool cancelTransfer(const std::string& transferId);
	bool pauseTransfer(const std::string& transgerId);
	bool resumetransfer(const std::string& transferId);
	void clearCompletedTransfers();
	bool clearTransfer(const std::string& transferId);
	bool isDeviceAvailable() const;

	struct StorageInfo {
		size_t totalSpace;
		size_t freeSpace;
		size_t usedSpace;
		double useagePercent;
	};

	struct ValidationResult {
		bool isValid;
		std::string error;
		size_t fileSize;
	};

	ValidationResult validateFile(const std::string& filePath);

private:
	std::shared_ptr<PSPDevice> device_;
	std::shared_ptr<FileTransfer> fileTransfer_;
	std::map<std::string, TransferInfo> transfers_;
	std::mutex transfersMutex_;
	std::string generateTransferId();

	void updateProcess(
		const std::string& transferId,
		size_t bytesTransferred,
		double speed
	);

	void completeTransfer(const std::string& transferId);
	void failTransfer(const std::string& trensferId, const std::string& error);

	void onTransferProgress(
		const std::string& transferId,
		size_t bytesTransferred,
		size_t totalBytes,
		double speed
	);

	bool fileExists(const std::string& path) const;
	size_t getFileSize(const std::string& path) const;
	
	long long getCurrenttime() const;
	long long calculateTimeRemaining(
		size_t bytesTransferred,
		size_t totalBytes,
		double speed
	) const;

	std::atomic<int> transferCounter_;
};