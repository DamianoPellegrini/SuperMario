#ifndef _SHADER_HPP
#define _SHADER_HPP

namespace engine {
    namespace renderer {
        class shader {
        private:
            uint32_t shader_id; // Program ID
        public:
            shader(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path);
            ~shader();

            void use() const;
            inline const uint32_t& id() const { return shader_id; };
        };
    }
}

#endif