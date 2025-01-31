/*
				Include "a_vpn_checker.inc"
    				by MrHan aka Mateusz
*/

#include <a_samp>

stock AbraKadabraChecker(playerid)
{
	new ip[16], string[256];
    GetPlayerIp(playerid, ip, sizeof(ip));
    
    format(string, sizeof(string), "proxycheck.io/v2/%s?vpn=1", ip);
    HTTP(playerid, HTTP_GET, string, "", "CheckProcess");
}

forward CheckProcess(playerid, response_code, data[]);
public CheckProcess(playerid, response_code, data[])
{
	new ip[16];
	GetPlayerIp(playerid, ip, sizeof(ip));
	
	if(strcmp(ip, "127.0.0.1", true) == 0) return 1;
	
	if(response_code == 200)
	{
		if(strfind(data, "\"proxy\": \"yes\"", true) != -1)
		{
            printf("%s[%d] использует VPN: %s.", GetName(playerid), playerid, ip);
			return 1;
		}
	}
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    KnoxSecurePlayerConnect(playerid);
    return 1;
}

