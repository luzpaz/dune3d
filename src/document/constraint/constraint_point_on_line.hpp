#pragma once
#include "constraint.hpp"
#include "document/entity/entity_and_point.hpp"

namespace dune3d {

class Entity;

class ConstraintPointOnLine : public Constraint {
public:
    explicit ConstraintPointOnLine(const UUID &uu);
    explicit ConstraintPointOnLine(const UUID &uu, const json &j);
    static constexpr Type s_type = Type::POINT_ON_LINE;
    Type get_type() const override
    {
        return s_type;
    }
    json serialize() const override;
    std::unique_ptr<Constraint> clone() const override;

    EntityAndPoint m_point;
    UUID m_line;
    UUID m_wrkpl;

    double m_val = 1;

    std::set<UUID> get_referenced_entities() const override;

    void accept(ConstraintVisitor &visitor) const override;

    bool replace_point(const EntityAndPoint &old_point, const EntityAndPoint &new_point) override;
};

} // namespace dune3d
