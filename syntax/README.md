# Submodule to describe syntax

Need to describe base syntax of chosen language and produce layouts(container for models) of models(syntax trasnlation unit)

Consists:
- Interface
- Generic (Main syntax units)
- Cpp (Cpp syntax units)

# Extension

When you need to extend your syntax units to another language, you need:
- **Add submodule** (for example. rust, c)
- **Extend generic abstractions** to target language(gen::Comment, gen::RVal, etc.)