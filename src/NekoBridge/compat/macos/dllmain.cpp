// DllMain for macOS
__attribute__((constructor)) void DllLoad() {}

__attribute__((destructor)) void DllUnload() {}