#include "LuaBinding/LuaWrapper.hpp"
#include "LuaBinding/lua_utility.hpp"
#include "AppFrame.h"
#include "lauxlib.h"
#include "lua.h"
#include <cassert>

// 微软我日你仙人
#ifdef PlaySound
#undef PlaySound
#endif

void LuaSTGPlus::LuaWrapper::AudioWrapper::Register(lua_State* L)noexcept
{
    struct Wrapper
    {
        static int ListAudioDevice(lua_State* L)
        {
            if (!LAPP.GetAppModel()->getAudioDevice())
            {
                return luaL_error(L, "engine not initialized");
            }
            lua::stack_t S(L);
            auto const refresh = S.get_value<bool>(1);
            uint32_t const count = LAPP.GetAppModel()->getAudioDevice()->getAudioDeviceCount(refresh);
            S.create_array(count);
            for (uint32_t i = 0; i < count; i += 1)
            {
                auto const name = LAPP.GetAppModel()->getAudioDevice()->getAudioDeviceName(i);
                S.set_array_value_zero_base<std::string_view>(i, name);
            }
            return 1;
        }
        static int ChangeAudioDevice(lua_State* L)
        {
            if (!LAPP.GetAppModel()->getAudioDevice())
            {
                return luaL_error(L, "engine not initialized");
            }
            lua::stack_t S(L);
            auto const name = S.get_value<std::string_view>(1);
            auto const result = LAPP.GetAppModel()->getAudioDevice()->setTargetAudioDevice(name);
            S.push_value<bool>(result);
            return 1;
        }
        static int GetCurrentAudioDeviceName(lua_State* L)
        {
            if (!LAPP.GetAppModel()->getAudioDevice())
            {
                return luaL_error(L, "engine not initialized");
            }
            lua::stack_t S(L);
            auto const result = LAPP.GetAppModel()->getAudioDevice()->getCurrentAudioDeviceName();
            S.push_value<std::string_view>(result);
            return 1;
        }

        static int PlaySound(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceSoundEffect> p = LRES.FindSound(s);
            if (!p)
                return luaL_error(L, "sound '%s' not found.", s);
            p->Play((float)luaL_checknumber(L, 2), (float)luaL_optnumber(L, 3, 0.0));
            return 0;
        }
        static int StopSound(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceSoundEffect> p = LRES.FindSound(s);
            if (!p)
                return luaL_error(L, "sound '%s' not found.", s);
            p->Stop();
            return 0;
        }
        static int PauseSound(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceSoundEffect> p = LRES.FindSound(s);
            if (!p)
                return luaL_error(L, "sound '%s' not found.", s);
            p->Pause();
            return 0;
        }
        static int ResumeSound(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceSoundEffect> p = LRES.FindSound(s);
            if (!p)
                return luaL_error(L, "sound '%s' not found.", s);
            p->Resume();
            return 0;
        }
        static int GetSoundState(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceSoundEffect> p = LRES.FindSound(s);
            if (!p)
                return luaL_error(L, "sound '%s' not found.", s);
            if (p->IsPlaying())
                lua_pushstring(L, "playing");
            else if (p->IsStopped())
                lua_pushstring(L, "stopped");
            else
                lua_pushstring(L, "paused");
            return 1;
        }
        static int SetSEVolume(lua_State* L)
        {
            float v = static_cast<float>(luaL_checknumber(L, 1));
            LAPP.SetSEVolume(v);
            return 0;
        }
        static int GetSEVolume(lua_State* L)
        {
            lua_pushnumber(L, LAPP.GetSEVolume());
            return 1;
        }
        static int SetSESpeed(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            float speed = (float)luaL_checknumber(L, 2);
            Core::ScopeObject<IResourceSoundEffect> p = LRES.FindSound(s);
            if (!p)
                return luaL_error(L, "sound '%s' not found.", s);
            if (!p->SetSpeed(speed))
                return luaL_error(L, "Can't set sound('%s') playing speed.", s);
            return 0;
        }
        static int GetSESpeed(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceSoundEffect> p = LRES.FindSound(s);
            if (!p)
                return luaL_error(L, "sound '%s' not found.", s);
            lua_pushnumber(L, p->GetSpeed());
            return 1;
        }
        static int UpdateSound(lua_State*)noexcept
        {
            // Removed method
            // TODO: why?
            return 0;
        }

        static int PlayMusic(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            p->Play((float)luaL_optnumber(L, 2, 1.), luaL_optnumber(L, 3, 0.));
            return 0;
        }
        static int StopMusic(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            p->Stop();
            return 0;
        }
        static int PauseMusic(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            p->Pause();
            return 0;
        }
        static int ResumeMusic(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            p->Resume();
            return 0;
        }
        static int GetMusicState(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            if (p->IsPlaying())
            {
                assert(!p->IsPaused() && !p->IsStopped());
                lua_pushstring(L, "playing");
            }
            else if (p->IsPaused())
            {
                assert(!p->IsStopped());
                lua_pushstring(L, "paused");
            }
            //else if (p->IsStopped())
                //lua_pushstring(L, "stopped");
            else
            {
                assert(p->IsStopped());
                lua_pushstring(L, "stopped");
            }
            //lua_pushstring(L, "paused");
            return 1;
        }
        static int GetMusicFFT(lua_State* L)
        {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            p->GetAudioPlayer()->updateFFT();
            size_t sz = p->GetAudioPlayer()->getFFTSize();
            float* fdata = p->GetAudioPlayer()->getFFT();
            if (!lua_istable(L, 2))
            {
                lua_createtable(L, (int)sz, 0);
            }
            for (int i = 0; i < (int)sz; i += 1)
            {
                lua_pushnumber(L, (lua_Number)fdata[i]);
                lua_rawseti(L, 2, i + 1);
            }
            return 1;
        }
        static int SetBGMVolume(lua_State* L)
        {
            if (lua_gettop(L) <= 1)
            {
                float x = static_cast<float>(luaL_checknumber(L, 1));
                LAPP.SetBGMVolume(x);
            }
            else
            {
                const char* s = luaL_checkstring(L, 1);
                float x = static_cast<float>(luaL_checknumber(L, 2));
                Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
                if (!p)
                    return luaL_error(L, "music '%s' not found.", s);
                p->SetVolume(x);
            }
            return 0;
        }
        static int GetBGMVolume(lua_State* L)
        {
            if (lua_gettop(L) == 0)
            {
                lua_pushnumber(L, LAPP.GetBGMVolume());
            }
            else if (lua_gettop(L) == 1)
            {
                const char* s = luaL_checkstring(L, 1);
                Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
                if (!p)
                    return luaL_error(L, "music '%s' not found.", s);
                lua_pushnumber(L, p->GetVolume());
            }
            return 1;
        }
        static int SetBGMSpeed(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            float speed = (float)luaL_checknumber(L, 2);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            if (!p->SetSpeed(speed))
                return luaL_error(L, "Can't set music('%s') playing speed.", s);
            return 0;
        }
        static int GetBGMSpeed(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            lua_pushnumber(L, p->GetSpeed());
            return 1;
        }
        static int SetBGMLoop(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            bool loop = lua_toboolean(L, 2);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            p->SetLoop(loop);
            return 0;
        }
        static int SetBGMLoopRange(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            double a = luaL_checknumber(L, 2);
            double b = luaL_checknumber(L, 3);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            p->SetLoopRange(a, b - a);
            return 0;
        }
        static int GetBGMLoop(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            lua_pushboolean(L, p->GetLoop());
            return 1;
        }
        static int GetBGMLoopRange(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            double a, b;
            p->GetLoopRange(a, b);
            lua_pushnumber(L, a);
            lua_pushnumber(L, b + a);
            return 2;
        }
        static int SetBGMTime(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            double a = luaL_checkint(L, 2);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            p->SetTime(a);
            return 0;
        }
        static int GetBGMTime(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            lua_pushnumber(L, p->GetTime());
            return 1;
        }
        static int GetBGMTotalTime(lua_State* L) {
            const char* s = luaL_checkstring(L, 1);
            Core::ScopeObject<IResourceMusic> p = LRES.FindMusic(s);
            if (!p)
                return luaL_error(L, "music '%s' not found.", s);
            lua_pushnumber(L, p->GetTotalTime());
            return 1;
        }
    };

    luaL_Reg const lib[] = {
        { "ListAudioDevice", &Wrapper::ListAudioDevice },
        { "ChangeAudioDevice", &Wrapper::ChangeAudioDevice },
        { "GetCurrentAudioDeviceName", &Wrapper::GetCurrentAudioDeviceName },

        { "PlaySound", &Wrapper::PlaySound },
        { "StopSound", &Wrapper::StopSound },
        { "PauseSound", &Wrapper::PauseSound },
        { "ResumeSound", &Wrapper::ResumeSound },
        { "GetSoundState", &Wrapper::GetSoundState },
        { "SetSEVolume", &Wrapper::SetSEVolume },
        { "GetSEVolume", &Wrapper::GetSEVolume },
        { "SetSESpeed", &Wrapper::SetSESpeed },
        { "GetSESpeed", &Wrapper::GetSESpeed },
        { "UpdateSound", &Wrapper::UpdateSound },

        { "PlayMusic", &Wrapper::PlayMusic },
        { "StopMusic", &Wrapper::StopMusic },
        { "PauseMusic", &Wrapper::PauseMusic },
        { "ResumeMusic", &Wrapper::ResumeMusic },
        { "GetMusicState", &Wrapper::GetMusicState },
        { "GetMusicFFT", &Wrapper::GetMusicFFT },
        { "SetBGMVolume", &Wrapper::SetBGMVolume },
        { "GetBGMVolume", &Wrapper::GetBGMVolume },
        { "SetBGMSpeed", &Wrapper::SetBGMSpeed },
        { "GetBGMSpeed", &Wrapper::GetBGMSpeed },
        { "SetBGMLoop", &Wrapper::SetBGMLoop },
        { "SetBGMLoopRange", &Wrapper::SetBGMLoopRange },
        { "GetBGMLoop", &Wrapper::GetBGMLoop },
        { "GetBGMLoopRange", &Wrapper::GetBGMLoopRange },
        { "SetBGMTime", &Wrapper::SetBGMTime },
        { "GetBGMTime", &Wrapper::GetBGMTime },
        { "GetBGMTotalTime", &Wrapper::GetBGMTotalTime },
        { NULL, NULL },
    };

    luaL_Reg const lib_empty[] = {
        { NULL, NULL },
    };

    luaL_register(L, LUASTG_LUA_LIBNAME, lib);          // ??? lstg
    luaL_register(L, LUASTG_LUA_LIBNAME ".Audio", lib); // ??? lstg lstg.Audio
    lua_setfield(L, -1, "Audio");                       // ??? lstg
    lua_pop(L, 1);                                      // ???
}
