//
// FileRotator.h : Declare the FileRotator class.
//
// FileRotator class will open a file, every time before writing in file, it will
// check for the file size, if it is more than a defined limit. It will rename the
// current file by appending 01, 02 ... etc. upto a kMaxFileCount and create a new file.
// When we will reach to the maxmium file count, it will will start deleting the old files.
//
// Note: Filesize check is approximate. It will just verify file size before writing into the file.
//
// Author: Manish K Agarwal (manish.k.agarwal@gmail.com)
//
// History:
//		18 March 2009 : Initial revision.
//
//

#ifndef __FILEROTATOR_H
#define __FILEROTATOR_H

#include <string>

class FileRotator
{
public:
	FileRotator(int maxFileSizeInBytes, const char *filename, int maxFileCount = 99);

	virtual ~FileRotator()
	{
		if (mFp != NULL) {
			fclose(mFp);
		}
	}

	bool Open();
	void Close();
	int Write(const char *str);

protected:
	bool IsMoreWriteAllowed() const;
	void PrepareToWrite();
	void RenameFile();

private:
	FILE* mFp;
	int mMaxFileSize; // In bytes
	const std::string mFilename;
	std::string mBaseFileName;
	std::string mFileExtn;
	int mNewRevisionCount;
	int mDeleteRevisionCount;
	const int kMaxFileCount;
	char mFormatStr[64];
};

#endif //__FILEROTATOR_H
