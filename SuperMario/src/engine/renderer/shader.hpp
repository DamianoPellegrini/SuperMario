#ifndef _SHADER_HPP
#define _SHADER_HPP

namespace engine::renderer {
    class shader {
    private:
        uint32_t shader_id; // Program ID
    public:
        shader(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path);
        ~shader();

        void bind() const;
        void unbind() const;
        inline const uint32_t& id() const { return shader_id; };

        template<class T>
        void set_uniform(const std::string_view name, const T& value) const;

        template<class T>
        const T get_uniform(const std::string_view name) const;
    };
} // namespace engine::renderer

#endif