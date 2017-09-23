# phpmem - A PHP Memory Hacking Extension

[Precompiled binaries](https://github.com/aequabit/phpmem/releases)

### Credits
- @frk1 and @ReactiioN for his [HazeDumper](https://github.com/frk1/hazedumper)
- @imi-tat0r for some C++ help
- @php for the PHP SDK

### Requirements
- Windows 7+
- Visual Studio 2015
- [PHP 7.1.9 x64 non thread safe](http://windows.php.net/downloads/releases/php-7.1.9-nts-Win32-VC14-x64.zip)
- [PHP 7.1.9 source code](http://windows.php.net/downloads/releases/php-7.1.9-src.zip)

### Setup
- extract the PHP source into `php-7.1.9-src` and the PHP binaries into `php-7.1.9`
- copy `php-7.1.9/dev/php7.lib` to `php-7.1.9-lib`
- open `src/phpmem.sln` and build the solution
- for installation instructions visit [the PHP docs](http://php.net/manual/de/install.pecl.windows.php#install.pecl.windows.loading)

### Info
- when developing, make sure to `require` `phpmem_polfill.php`. It provides the data types for `ReadProcessMemory` and `WriteProcessMemory`
- if you need CS:GO offsets, you can use my [HazeDumper parser](https://github.com/aequabit/hazedumper-php) for PHP

### Documentation
Opens a handle to a process.  
`int PHPMem::GetProcessHandle(string process)`  
Return: `int processHandle` or `false`  

Gets the base addess of a loaded module.  
`int PHPMem::GetModuleBase(int handle, string module)`  
Return: `int moduleBaseAddress` or `false`  

Reads data from the specified address.  
`any PHPMem::ReadProcessMemory(int handle, int address, int type)`  
Return: `any data` or `false`  

Writes the specified data to the specified address.  
`int PHPMem::WriteProcessMemory(int handle, int address, any value, int type)`  
Return: `int lengthOfWrittenData` or `false`
