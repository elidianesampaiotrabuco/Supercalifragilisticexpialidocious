#include <Geode/Geode.hpp>

using namespace geode::prelude;

inline static std::string server = Mod::get()->getDescription().value_or("sadlya.ps.fhgdps.com");
inline static auto links = matjson::parse(R"({
	"asdasd": "asdasd",
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
		url = string::replace(url, "www.boomlings.com/database", server);
		url = string::replace(url, "boomlings.com/database", server);
		req->setUrl(url.c_str());
		return CCHttpClient::send(req);
	}
};
//url open
#include <Geode/modify/CCApplication.hpp>
class $modify(CCApplicationLinksReplace, CCApplication) {
	$override void openURL(const char* psz) {
		std::string url = psz;
		url = not links.contains(url) ? url : links[url].asString().unwrapOr(url);
		url = string::replace(url, "https://www.twitter.com/", "https://x.com/");
		url = string::replace(url, "www.boomlings.com/database", server);
		url = string::replace(url, "boomlings.com/database", server);
		//log::debug("{}.url = {}", __FUNCTION__, url);
		return CCApplication::openURL(url.data());
	}
};