# Bypass-Sandbox-Evasion

Sandboxes are commonly used to analyze malware. They provide a temporary, isolated, and secure environment in which to observe whether a suspicious file exhibits any malicious behavior. However, malware developers have also developed methods to evade sandboxes and analysis environments. One such method is to perform checks to determine whether the machine the malware is being executed on is being operated by a real user. One such check is the RAM size. If the RAM size is unrealistically small (e.g., 1GB), it may indicate that the machine is a sandbox. If the malware detects a sandbox, it will not execute its true malicious behavior and may appear to be a benign file

# Details

* The ``GetPhysicallyInstalledSystemMemory`` API retrieves the amount of RAM that is physically installed on the computer from the SMBIOS firmware tables. It takes a ``PULONGLONG`` parameter and returns ``TRUE`` if the function succeeds, setting the ``TotalMemoryInKilobytes`` to a nonzero value. If the function fails, it returns ``FALSE``.
 
  ![image](https://user-images.githubusercontent.com/60795188/184276948-519eebf4-04b8-4efe-b5ad-846db7947ac9.png)
  ![image](https://user-images.githubusercontent.com/60795188/184352373-7672957c-aba6-481e-8d66-c3954391f44f.png)

* The amount of physical memory retrieved by the ```GetPhysicallyInstalledSystemMemory``` function must be equal to or greater than the amount reported by the ```GlobalMemoryStatusEx``` function; if it is less, the SMBIOS data is malformed and the function fails with ```ERROR_INVALID_DATA```, Malformed SMBIOS data may indicate a problem with the user's computer .

  ![image](https://user-images.githubusercontent.com/60795188/184278957-1a50b12b-7113-4296-ade7-ba5ec0c75348.png)

* The register ``rcx`` holds the parameter ``TotalMemoryInKilobytes``. To overwrite the jump address of ``GetPhysicallyInstalledSystemMemory``, I use the following opcodes: ``mov qword ptr ss:[rcx],4193B840``. This moves the value ``4193B840`` (or 1.1 TB) to ``rcx``. Then, the ret instruction is used to pop the return address off the stack and jump to it, Therefore, whenever ``GetPhysicallyInstalledSystemMemory`` is called, it will set ``rcx`` to the custom value."

  ![image](https://user-images.githubusercontent.com/60795188/184280098-474187ba-5979-4405-91e3-a3576e206925.png)

# VID 

   https://user-images.githubusercontent.com/60795188/184030477-2c6dc38a-0ef6-41ca-a118-88e9d8ee9e45.mp4
