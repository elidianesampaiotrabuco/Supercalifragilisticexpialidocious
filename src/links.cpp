#include <Geode/Geode.hpp>

using namespace geode::prelude;

inline static std::string server = "sadlya.ps.fhgdps.com";
inline static auto links = matjson::parse(R"({
	"asdasd": "asdasd",
    "https://clck.su/TzzLu": "https://x.com/MSVE640/status/1956551495807029466",
	"https://www.boomlings.com/GDEditor": "https://github.com/lil2kki/REMINA/wiki/Editor-Guide-(New-Features-List)#",
	"https://www.robtopgames.com": "https://elidianesampaiotrabuco.github.io",
	"https://www.boomlings.com/database/accounts/accountManagement.php": "https://sadlya.ps.fhgdps.com",
	"https://store.steampowered.com/recommended/recommendgame/322170": "https://gdpshub.com/gdps/5556",
	"https://discord.com/invite/geometrydash": "https://discord.gg/NXbbv2HZGg",
	"https://twitter.com/robtopgames": "https://x.com/MSVE640",
	"https://www.youtube.com/user/RobTopGames": "https://peertube.wtf/c/msve640/videos"
})").unwrapOrDefault();

//send
#include <Geode/modify/CCHttpClient.hpp>
class $modify(CCHttpClientLinksReplace, CCHttpClient) {
	void send(CCHttpRequest * req) {
		std::string url = req->getUrl();
		if (getMod()->getSettingValue<bool>("redir request urls")) {
			url = string::replace(url, "www.boomlings.com/database", server);
			url = string::replace(url, "boomlings.com/database", server);
		}
		else {
			url = string::replace(url, server, "www.boomlings.com/database");
		}
		req->setUrl(url.c_str());
		//log::info("null check: ", server); - debug actually
		return CCHttpClient::send(req);
	}
};

//url open
#include <Geode/modify/CCApplication.hpp>
class $modify(CCApplicationLinksReplace, CCApplication) {
	$override void openURL(const char* psz) {
		std::string url = psz;
		url = not links.contains(url) ? url : links[url].asString().unwrapOr(url);
		if (getMod()->getSettingValue<bool>("redir request urls")) {
			url = string::replace(url, "https://www.twitter.com/", "https://t.me/");
			url = string::replace(url, "www.boomlings.com/database", server);
			url = string::replace(url, "boomlings.com/database", server);
		}
		else {
			url = string::replace(url, server, "www.boomlings.com/database");
		}
		//log::debug("{}.url = {}", __FUNCTION__, url);
		return CCApplication::openURL(url.data());
	}
};