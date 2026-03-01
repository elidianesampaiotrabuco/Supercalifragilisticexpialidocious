#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
using namespace geode::prelude;

#if defined(__APPLE__)
#define NOT_APPLE(...)
#else
#define NOT_APPLE(...) __VA_ARGS__
#endif

#include <regex>

#include <libs/httplib.h>
#include <libs/CCLabelBMFontAnimated.h>

class DataNode : public CCNode {
public:
	std::string _json_str;
	auto get(std::string_view key) {
		return matjson::parse(_json_str).unwrapOrDefault()[key];
	}
	void set(std::string_view key, matjson::Value val) {
		auto parse = matjson::parse(_json_str).unwrapOrDefault();
		parse[key] = val;
		_json_str = parse.dump(matjson::NO_INDENTATION);
	}
	CREATE_FUNC(DataNode);
	static auto create(std::string id) {
		auto a = create();
		a->setID(id);
		return a;
	}
	static auto at(CCNode* container, std::string id = "") {
		auto me = typeinfo_cast<DataNode*>(container->getUserObject(id));
		if (!me) {
			me = create();
			container->setUserObject(id, me);
			log::debug("creating data node {} for {}...", me, container);
		}
		return me;
	}
};

class KeyEventListener : public CCNode, public CCKeyboardDelegate {
public:
	KeyEventListener() { CCKeyboardDispatcher::get()->addDelegate(this); };
	void onExit() override {
		CCNode::onExit();
		CCKeyboardDispatcher::get()->removeDelegate(this);
	}
	CREATE_FUNC(KeyEventListener);
	void keyDown(enumKeyCodes key) override {
		if (m_keyDown) m_keyDown(key);
	}
	void keyUp(enumKeyCodes key) override {
		if (m_keyUp) m_keyUp(key);
	}
	auto onKeyDown(std::function<void(enumKeyCodes key)> keyDown) { m_keyDown = keyDown; return this; }
	auto onKeyUp(std::function<void(enumKeyCodes key)> keyUp) { m_keyUp = keyUp; return this; }

	std::function<void(enumKeyCodes key)> m_keyDown = [](enumKeyCodes) {};
	std::function<void(enumKeyCodes key)> m_keyUp = [](enumKeyCodes) {};
};

namespace fs {
	using namespace std::filesystem;
	static inline auto err = std::error_code{};
};


namespace geode::cocos {
	static inline std::string getClassName(cocos2d::CCObject* obj, bool removeNamespace = false) {
		if (!obj) return "nullptr";

		std::string ret;

#ifdef GEODE_IS_WINDOWS
		ret = typeid(*obj).name();
		constexpr std::string_view classPrefix = "class ";
		constexpr std::string_view structPrefix = "struct ";

		auto removeAll = [](std::string& str, std::string_view prefix) {
			size_t pos = 0;
			while ((pos = str.find(prefix, pos)) != std::string::npos) {
				str.erase(pos, prefix.size());
			}
			};

		removeAll(ret, classPrefix);
		removeAll(ret, structPrefix);
#else 
		int status = 0;
		auto demangled = abi::__cxa_demangle(typeid(*obj).name(), nullptr, nullptr, &status);
		if (status == 0 && demangled) {
			ret = demangled;
		}
		free(demangled);
#endif
		if (removeNamespace) {
			if (auto pos = ret.rfind("::"); pos != std::string::npos) {
				ret = ret.substr(pos + 2);
			}
		}

		return ret;
	};

#include  <random>
#include  <iterator>
	namespace geode::cocos::geode::utils {
		template<typename Iter, typename RandomGenerator>
		Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
			std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
			std::advance(start, dis(g));
			return start;
		};
		template<typename Iter>
		Iter select_randomly_alt(Iter start, Iter end) {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			return select_randomly(start, end, gen);
		}
		bool rndb(int rarity = 1) {
			auto varsVec = std::vector<bool>();
			varsVec.push_back(true);
			while (rarity > 0) {
				rarity = rarity - 1;
				varsVec.push_back(false);
			}
			auto rtn = *select_randomly_alt(varsVec.begin(), varsVec.end());
			//log::debug("{}({}) = {} of {}", __func__, variants, rtn, varsVec);
			return rtn;
		}
	}

	//auto pLoadingLayerRef = Ref<LoadingLayer>(nullptr);
}