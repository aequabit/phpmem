#include "phpmem.h"

zend_class_entry *car_ce;

enum DataType {
	TYPE_LONG = 1,
	TYPE_STRING,
	TYPE_BOOL,
	TYPE_DOUBLE,
	TYPE_FLOAT
};

PHP_METHOD(PHPMem, GetProcessHandle) {
	char* arg_processName;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg_processName) == FAILURE)
		RETURN_FALSE;

	memory* mem = memory::GetInstance();

	std::string szProcessName = std::string(arg_processName);
	bool success = mem->OpenProcessHandle(szProcessName);
	if (!success)
		RETURN_FALSE;
	
	RETURN_LONG((long)mem->GetProcessHandle());
}

PHP_METHOD(PHPMem, GetModuleBase) {
	long arg_handle;
	char* arg_moduleName;
	long strLen;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &arg_handle, &arg_moduleName, &strLen) == FAILURE)
		RETURN_FALSE;

	memory* mem = memory::GetInstance();
	mem->SetHandle((HANDLE)arg_handle);

	auto szModuleName = std::string(arg_moduleName);
	DWORD moduleBase = mem->GetModuleBase(szModuleName);
	if (moduleBase == -1)
		RETURN_FALSE;

	RETURN_LONG(moduleBase);
}

PHP_METHOD(PHPMem, ReadProcessMemory) {
	long arg_handle;
	long arg_address;
	long arg_type;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &arg_handle, &arg_address, &arg_type) == FAILURE)
		RETURN_FALSE;

	memory* mem = memory::GetInstance();
	mem->SetHandle((HANDLE)arg_handle);
	
	DataType type = (DataType)arg_type;
	if (type == DataType::TYPE_LONG) {
		long result = mem->Read<long>(arg_address);
		RETURN_LONG(result);
	}
	else if (type == DataType::TYPE_STRING) {
		std::string result = mem->ReadString(arg_address);
		RETURN_STRING(result.c_str());
	}
	else if (type == DataType::TYPE_BOOL) {
		bool result = mem->Read<bool>(arg_address);
		RETURN_BOOL(result);
	}
	else if (type == TYPE_DOUBLE) {
		double result = mem->Read<double>(arg_address);
		RETURN_DOUBLE(result);
	}
	else if (type == TYPE_FLOAT) {
		float result = mem->Read<float>(arg_address);
		RETURN_DOUBLE(result);
	}

	RETURN_FALSE;
}

PHP_METHOD(PHPMem, WriteProcessMemory) {
	long arg_handle;
	long arg_address;
	zval* arg_value;
	long arg_type;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llzl", &arg_handle, &arg_address, &arg_value, &arg_type) == FAILURE)
		RETURN_FALSE;

	memory* mem = memory::GetInstance();
	mem->SetHandle((HANDLE)arg_handle);

	int bytesWritten = 0;
	DataType type = (DataType)arg_type;

	if (type == DataType::TYPE_LONG) {
		int value = Z_LVAL_P(arg_value);
		bytesWritten = mem->Write<long>(arg_address, &value);
	}
	else if (type == DataType::TYPE_STRING) {
		char* value = Z_STRVAL_P(arg_value);
		bytesWritten = mem->Write<char*>(arg_address, &value);
	}
	else if (type == DataType::TYPE_BOOL) {
		bool value = Z_LVAL_P(arg_value);
		bytesWritten = mem->Write<bool>(arg_address, &value);
	}
	else if (type == DataType::TYPE_DOUBLE) {
		double value = Z_DVAL_P(arg_value);
		bytesWritten = mem->Write<double>(arg_address, &value);
	}
	else if (type == DataType::TYPE_FLOAT) {
		float value = Z_DVAL_P(arg_value);
		bytesWritten = mem->Write<float>(arg_address, &value);
	}
	else RETURN_FALSE;

	RETURN_LONG(bytesWritten);
}

PHP_FUNCTION(phpmem_info) {
	std::string info(PHPMEM_NAME);
	info.append(" v");
	info.append(PHPMEM_VERSION);
	info.append("\ncreated by aequabit\nhttps://github.com/aequabit/phpmem");
	RETURN_STRING(info.c_str());
}

zend_function_entry phpmem_functions[] = {
	PHP_FE(phpmem_info, AI_None)
	PHP_FE_END
};

zend_function_entry phpmem_methods[] = {
	PHP_ME(PHPMem, GetProcessHandle, AI_String, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(PHPMem, GetModuleBase, AI_LongString, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(PHPMem, ReadProcessMemory, AI_LongLongLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(PHPMem, WriteProcessMemory, AI_LongLongAnyLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(phpmem_init) {
	zend_class_entry pm;
	INIT_CLASS_ENTRY(pm, "PHPMem", phpmem_methods);
	car_ce = zend_register_internal_class(&pm TSRMLS_CC);
	return SUCCESS;
}

zend_module_entry phpmem_module_entry = {
	STANDARD_MODULE_HEADER,
	PHPMEM_NAME,
	phpmem_functions,
	PHP_MINIT(phpmem_init),
	NULL,
	NULL,
	NULL,
	NULL,
	PHPMEM_VERSION,
	STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(phpmem)