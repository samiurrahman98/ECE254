SET PATH=c:\Software\Keil\ARM\ARMCC\bin\;C:\ProgramData\Oracle\Java\javapath;C:\Software\Python36\Scripts\;C:\Software\Python36\;c:\Software\Perl64\site\bin;c:\Software\Perl64\bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;c:\Program Files\TortoiseSVN\bin;C:\Program Files (x86)\GtkSharp\2.12\bin;C:\Program Files\MATLAB\R2017a\runtime\win64;C:\Program Files\MATLAB\R2017a\bin;c:\Program Files (x86)\PuTTY\;c:\Program Files\PuTTY\;C:\Program Files (x86)\WinSCP;C:\Program Files (x86)\MiKTeX 2.9\miktex\bin\;C:\Program Files\Keysight\IO Libraries Suite\bin;C:\Program Files\IVI Foundation\VISA\Win64\ktvisa;C:\Program Files\IVI Foundation\VISA\Win64\bin;C:\Program Files (x86)\Keysight\IO Libraries Suite\bin;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\ktvisa;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\bin;C:\Program Files (x86)\IVI Foundation\IVI\bin;C:\Program Files\IVI Foundation\IVI\bin;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;c:\Program Files (x86)\IVI Foundation\VISA\winnt\agvisa
SET CPU_TYPE=Cortex-M3
SET CPU_VENDOR=ARM
SET UV2_TARGET=CM3_LE
SET CPU_CLOCK=0x00B71B00
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_task.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_system.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_event.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_list.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_mailbox.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_semaphore.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_time.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_timer.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_mutex.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_robin.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_membox.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_task_ext.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_membox_ext.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\cm3_le\svc_table._ia"
"c:\Software\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\hal_cm3.__i"
"c:\Software\Keil\ARM\ARMCC\bin\ArmAr" --Via "ArInp.Scr"
cmd.exe /C copy ArInp.Scr CM3_LE\BuildLib.scr
