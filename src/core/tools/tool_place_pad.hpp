#pragma once
#include "core/tool.hpp"
#include "parameter/set.hpp"

namespace horizon {
class ToolPlacePad : public ToolBase {
public:
    using ToolBase::ToolBase;
    ToolResponse begin(const ToolArgs &args) override;
    ToolResponse update(const ToolArgs &args) override;
    bool can_begin() override;
    std::set<InToolActionID> get_actions() const override
    {
        using I = InToolActionID;
        return {
                I::LMB, I::CANCEL, I::RMB, I::ROTATE, I::EDIT,
        };
    }

private:
    std::shared_ptr<const class Padstack> padstack;
    class Pad *temp = nullptr;
    ParameterSet temp_param;
    void create_pad(const Coordi &c);
};
} // namespace horizon
