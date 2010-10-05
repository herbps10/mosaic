bool fileExists(string path) {
	struct stat fileInfo;
	int intStat;

	intStat = stat(path.c_str(), &fileInfo);

	if(intStat == 0) {
		return true;
	}
	else {
		return false;
	}
}
