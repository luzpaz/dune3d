#pragma once
#include "constraint.hpp"
#include "iconstraint_datum.hpp"
#include <glm/glm.hpp>

namespace dune3d {

class Entity;

class ConstraintAngleBase : public Constraint {
public:
    explicit ConstraintAngleBase(const UUID &uu);
    explicit ConstraintAngleBase(const UUID &uu, const json &j);

    json serialize() const override;

    UUID m_entity1;
    UUID m_entity2;
    UUID m_wrkpl;

    std::set<UUID> get_referenced_entities() const override;
};

class ConstraintLinesPerpendicular : public ConstraintAngleBase {
public:
    using ConstraintAngleBase::ConstraintAngleBase;

    static constexpr Type s_type = Type::LINES_PERPENDICULAR;
    Type get_type() const override
    {
        return s_type;
    }

    std::unique_ptr<Constraint> clone() const override;
    void accept(ConstraintVisitor &visitor) const override;
};

class ConstraintLinesAngle : public ConstraintAngleBase, public IConstraintDatum {
public:
    using ConstraintAngleBase::ConstraintAngleBase;
    explicit ConstraintLinesAngle(const UUID &uu, const json &j);
    json serialize() const override;


    static constexpr Type s_type = Type::LINES_ANGLE;
    Type get_type() const override
    {
        return s_type;
    }

    double m_angle = 0;
    bool m_negative = false;
    glm::dvec3 m_offset = {0, 0, 0};
    glm::dvec3 get_origin(const Document &doc) const;

    bool is_movable() const override
    {
        return true;
    }

    double get_datum() const override
    {
        return m_angle;
    }

    void set_datum(double d) override
    {
        m_angle = d;
    }

    DatumUnit get_datum_unit() const override
    {
        return DatumUnit::DEGREE;
    }

    std::pair<double, double> get_datum_range() const override
    {
        return {0, 360};
    }

    std::string get_datum_name() const override
    {
        return "Angle";
    }

    std::unique_ptr<Constraint> clone() const override;
    void accept(ConstraintVisitor &visitor) const override;
};

} // namespace dune3d
