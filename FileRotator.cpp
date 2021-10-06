//
// FileRotator.cpp : Define the FileRotator memebrs.
//
// Author: Manish K Agarwal (manish.k.agarwal@gmail.com)
//
// History:
//		18 March 2009 : Initial revision.
//
//
//
#include <stdio.h>
#include <string.h>
#include "FileRotator.h"


//
// Constructor
//
FileRotator::FileRotator(int maxFileSizeInBytes, const char *filename, int maxFileCount)
		: mFp(NULL), mMaxFileSize(maxFileSizeInBytes), mFilename(filename), mNewRevisionCount(0),
		mDeleteRevisionCount(0), kMaxFileCount(maxFileCount)
{
	// Find last postion of . (dot)
	size_t dotIndex = mFilename.rfind(".");

	if (dotIndex != -1) {
		mBaseFileName = mFilename.substr(0, dotIndex);
		mFileExtn = mFilename.substr(dotIndex, mFilename.length());
	}
	else {
		mBaseFileName = mFilename;
		mFileExtn = "";
	}

	int numberOfDigits = 0;
	int maxCount = 1;
	// count the digits
	while (maxCount < kMaxFileCount) {
		numberOfDigits++;
		maxCount = maxCount * 10;
	}
	memset(mFormatStr, 0, sizeof(mFormatStr));

	sprintf(mFormatStr, "%s0%dd%s", "%s%", numberOfDigits, "%s"); // generate a string like "%s%02d%s"
}
//
// FileRotator: Write buffer into File.
//
int FileRotator::Write(const char *str)
{
	PrepareToWrite();

	return fprintf(mFp, "%s", str);
}

//
// Check if we write more in current opened file.
//
bool FileRotator::IsMoreWriteAllowed() const
{
	FILE * pFile = NULL;
	long fileSize = 0;

	pFile = fopen (mFilename.c_str(), "rb");

	if (pFile != NULL) {
		fseek (pFile, 0, SEEK_END);
		fileSize = ftell(pFile);
		fclose (pFile);
	}

	if (fileSize < mMaxFileSize) {
		return true;
	}

	return false;
}

//
// Open the file, if required get the next name.
//
bool FileRotator::Open()
{
	if (IsMoreWriteAllowed()) {
		//Open current log file to write.
		mFp = fopen(mFilename.c_str(), "a+");
	}
	else {
		// Rename it to unique name.
		RenameFile();

		//Now open a new log file to write.
		mFp = fopen(mFilename.c_str(), "w+");
	}
	return (mFp != NULL);
}

void FileRotator::Close()
{
	fclose(mFp);
	mFp = NULL;
}

//
// PrepareToWrite: validate file size, if required, rename existing file and reopen a new file.
//
void FileRotator::PrepareToWrite()
{
	if (!IsMoreWriteAllowed()) {
		// close current file
		fclose(mFp);

		// Rename it to unique name.
		RenameFile();

		// Now open a new file to write.
		mFp = fopen(mFilename.c_str(), "w+");
	}
}

//
// Rename existing file name to next file name. Also delete old file if required.
//
void FileRotator::RenameFile()
{
	char newFilename[1024] = "";

	int i = 0;
	// Generate an available filename, if mNewRevisionCount count reached to its max limit
	// no need to reset it. We will delete a file and create new one.
	for (i = mNewRevisionCount; i <= kMaxFileCount; i++){
		sprintf(newFilename, mFormatStr, mBaseFileName.c_str(), i, mFileExtn.c_str());

		// Rename logfile and keep a version of it with name file01.txt
		mFp = fopen(newFilename, "r");
		if (mFp == NULL) {
			// file doesn't exist.
			rename(mFilename.c_str(), newFilename);
			mNewRevisionCount = i + 1;
			break;
		}
		else {
			// if file exists close it and try for another file.
			fclose(mFp);
		}
	} // for

	if (i > kMaxFileCount) {
		// Now we have to delete the first file i.e. 00 
		// TODO: check the time stamp of file and delete the oldest file first.
		sprintf(newFilename, mFormatStr, mBaseFileName.c_str(), mDeleteRevisionCount, mFileExtn.c_str());
		if (mDeleteRevisionCount < kMaxFileCount) {
			mDeleteRevisionCount++;
		}
		else {
			mDeleteRevisionCount = 0;
		}

		// delete file file00.txt always
		remove(newFilename);
		// rename current file to new name.
		rename(mFilename.c_str(), newFilename);
	}
}

