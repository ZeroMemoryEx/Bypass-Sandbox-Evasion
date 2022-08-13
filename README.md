# Bypass-Sandbox-Evasion

* Sandboxes are widely used to analyse malwares , They provide a temporary, isolated and secure environment to observe if a suspicious file attempts anything malicious. 
Of course, Over time malware developers have also added methods to avoid sandboxes and analysis environments by performing various checks
to see if there is an actual user operating the machine the malware is being executed on, and one of those checks and the one that we will bypass is ram check eg an unrealistically small RAM size (e.g. 1GB) can be indicative of a sandbox ,If the malware detects a sandbox, it will not execute its true malicious behavior and therefore appears to be another benign file. 

# Details

* the ```GetPhysicallyInstalledSystemMemory``` API Retrieves the amount of RAM that is physically installed on the computer from the SMBIOS firmware tables, it takes ```PULONGLONG``` in parameters and returns TRUE if function succeeds and sets the ```TotalMemoryInKilobytes``` to a nonzero value otherwise it returns FALSE.
 
  ![image](https://user-images.githubusercontent.com/60795188/184276948-519eebf4-04b8-4efe-b5ad-846db7947ac9.png)
  ![image](https://user-images.githubusercontent.com/60795188/184352373-7672957c-aba6-481e-8d66-c3954391f44f.png)

* The amount of physical memory retrieved by the ```GetPhysicallyInstalledSystemMemory``` function must be equal to or greater than the amount reported by the ```GlobalMemoryStatusEx``` function; if it is less, the SMBIOS data is malformed and the function fails with ```ERROR_INVALID_DATA```, Malformed SMBIOS data may indicate a problem with the user's computer .

  ![image](https://user-images.githubusercontent.com/60795188/184278957-1a50b12b-7113-4296-ade7-ba5ec0c75348.png)

* the Register rcx hold our parameter ```TotalMemoryInKilobytes``` , so i overwrite the jump address of ```GetPhysicallyInstalledSystemMemory``` with our custom opcodes 
```mov qword ptr ss:[rcx],4193B840```  we mov value 4193B840  or 1,1 TB  (you can change it with your needs) to rcx then we return ,```ret``` instruction will pops the return address off the stack then jumps to it ,so whenever  ```GetPhysicallyInstalledSystemMemory``` gets called it will set rcx with our custom value .

  ![image](https://user-images.githubusercontent.com/60795188/184280098-474187ba-5979-4405-91e3-a3576e206925.png)

# VID 

   https://user-images.githubusercontent.com/60795188/184030477-2c6dc38a-0ef6-41ca-a118-88e9d8ee9e45.mp4
