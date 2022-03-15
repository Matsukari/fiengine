#ifndef CONFIGURES_H
#define CONFIGURES_H


struct Key_Configure {
public:
	Key_Configure(std::vector<SDL_Scancode> _keys);
	Key_Configure();

	void Re_Configure(std::vector<SDL_Scancode> _keys);
	void Save(bool newfile = false);
	void Load(std::string filename);

	std::vector<SDL_Scancode> keys;

private:
	// Storage
	std::fstream m_data_file;

}; 
Key_Configure::Key_Configure(std::vector<SDL_Scancode> _keys)
{
		this->Re_Configure(_keys);
};

Key_Configure::~Key_Configure()
{

}
void Key_Configure::Re_Configure(std::vector<SDL_Scancode> _keys)
{
	if (_keys.size() == KEY_TOTAL) {
		keys = _keys;
		for (unsigned short i = 0; i < _keys.size(); i++)
			std::cout << "\n" << _keys[i] ;
	}
}
void Key_Configure::Save(bool newfile = false)
{
	if (keys.size() == KEY_TOTAL) {
		std::string filename{"Data/Key_Configure-"};
		if (newfile) {
			static int files = 1;
			filename = filename + std::to_string(files) + ".txt"; 
			files++;
		}

		printf("\nFilename : %s", filename.c_str());

		m_data_file.open(filename.c_str(), std::ios::out | std::ios::trunc);

		m_data_file << (int)keys.size() << " ";
		for (unsigned short i = 0; i < keys.size(); i++) {
			m_data_file << (int)keys[i] << " ";
		}

		m_data_file.close();
	}

}
// Under Construction. Load()
void Key_Configure::Load(std::string filename = "../../Data/Key_Configure.txt")
{
	m_data_file.open(filename.c_str(), std::ios::in);

	int length; m_data_file >> length;
	std::vector<int> temp(length);

	for (unsigned short i = 0; i < temp.size(); i++) {
		m_data_file >> temp[i];
		keys[i] = (SDL_Scancode)temp[i];
	}


	m_data_file.close();
}

#endif