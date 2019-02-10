/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#include <cloth/particleUpdaters.hpp>


/******************************************************************************
void update(float dt, ParticleData *p){
	size_t end_id = p->m_count_alive;
	for (size_t i = 0; i < end_id; ++i) {
		//do stuff
	}
}
******************************************************************************/

void GravityUpdater::update(float dt, ParticleData *p){
  size_t end_id = p->m_count_alive;

  glm::fvec4* acc = p->m_acc.get();

  for (size_t i = 0; i < end_id; ++i) {
    acc[i] += m_grav;
  }
}

void VerletPosUpdater::update(float dt, ParticleData *p) {
  size_t end_id = p->m_count_alive;

  glm::fvec4* pos = p->m_pos.get();
  glm::fvec4* prev_pos = p->m_pos_prev.get();
  glm::fvec4* acc = p->m_acc.get();
  glm::fvec4 temp;

  for (size_t i = 0; i < end_id; ++i) {
    if(pos[i].w == 0.f) {
      temp = pos[i];
      pos[i] += (pos[i] - prev_pos[i]) * (1.f - m_damp) + acc[i] * dt * dt;
      prev_pos[i] = temp;
      pos[i].w = temp.w;
    }
  }
}
void SpringUpdater::update(float dt, ParticleData *p) {

  auto pos = p->m_pos.get();
  auto prev = p->m_pos_prev.get();
  auto acc = p->m_acc.get();
  auto mass = p->m_mass.get();

  glm::fvec3 dist;
  float f, dx, dy;

  for(auto& s : *m_spring){
    dist = glm::fvec3(pos[(int)s.x] - pos[(int)s.y]);

    f = m_k * (glm::length(dist) - s.z);
    dist = glm::normalize(dist);
    dx = 0.1f * glm::dot(dist, glm::vec3(pos[(int)s.x] - prev[(int)s.x])) - f;
    dy = 0.1f * glm::dot(dist, glm::vec3(pos[(int)s.y] - prev[(int)s.y])) + f;
    acc[(int)s.x] += glm::fvec4(dx * dist, 0.f) / mass[(int)s.x];
    acc[(int)s.y] += glm::fvec4(dy * dist, 0.f) / mass[(int)s.y];
  }
}

void StretchUpdater::update(float dt, ParticleData *p) {
  glm::fvec4* pos = p->m_pos.get();
  auto struct_con = p->m_struct_con;
  auto shear_con = p->m_shear_con;
  auto bend_con = p->m_bend_con;

  for(int i = 0; i < m_iter; ++i){
    for(auto& s : *struct_con){
      maxStretch(s.z, pos[(int)s.x], pos[(int)s.y]);
    }
    for(auto& s : *shear_con){
      maxStretch(s.z, pos[(int)s.x], pos[(int)s.y]);
    }
    for(auto& s : *bend_con){
      maxStretch(s.z, pos[(int)s.x], pos[(int)s.y]);
    }
  }
}

void StretchUpdater::maxStretch(float rest, glm::fvec4& pos_1, glm::fvec4& pos_2) {
  glm::fvec3 dist = glm::fvec3(pos_1 - pos_2);
  glm::fvec3 dir = glm::normalize(dist);
  float len = glm::length(dist);
  //satisfy max distance constraint
  if ((len > rest * m_max) || (len < rest * m_min)) {
    glm::fvec3 f = dist * (1 - (rest * m_max) / len);

    glm::fvec3 corr = f * (1 - pos_1.w) * 0.5f * (1 + pos_2.w);
    pos_1 -= glm::fvec4(corr, 0.f);

    corr = f * (1 - pos_2.w) * 0.5f * (1 + pos_1.w);
    pos_2 += glm::fvec4(corr, 0.f);
  }
}

void NormalUpdater::update(float dt, ParticleData *p) {
  size_t end_id = p->m_count_alive;

  auto normal = p->m_normal.get();
  auto pos = p->m_pos.get();
  auto ind = p->m_indices;

  unsigned int a, b, c;
  glm::vec3 x, y, z, u, v, n;

  for(int i = 0; i < ind->size() / 3; ++i){
    a = ind->at(3 * i);
    b = ind->at(3 * i + 1);
    c = ind->at(3 * i + 2);

    x = glm::vec3(pos[a]);
    y = glm::vec3(pos[b]);
    z = glm::vec3(pos[c]);

    u = x - z; v = y - z;
    n = glm::normalize(glm::cross(u, v));

    normal[a] += glm::vec4(n, 0.f);
    normal[b] += glm::vec4(n, 0.f);
    normal[c] += glm::vec4(n, 0.f);

  }

  for (size_t i = 0; i < end_id; ++i) {
    normal[i] = glm::normalize(normal[i]);
  }

}

void SphereCollisionUpdater::update(float dt, ParticleData *p) {
  size_t end_id = p->m_count_alive;

  auto pos = p->m_pos.get();
  auto prev = p->m_pos_prev.get();
  glm::vec3 dist, mov, hit, norm, newpos, betw;

  for (size_t i = 0; i < end_id; ++i) {
    dist = glm::vec3(pos[i]) - m_pos;
    if(glm::length(dist) < m_r){
      mov = glm::normalize(dist) * m_r + m_pos;
      glm::intersectLineSphere(glm::vec3(pos[i]), glm::vec3(prev[i]), m_pos, m_r, hit, norm, newpos, betw);
      betw = hit - mov;
      newpos = mov + m_f * betw;
      newpos = glm::normalize(newpos - m_pos) * m_r + m_pos;
      pos[i].x = newpos.x;
      pos[i].y = newpos.y;
      pos[i].z = newpos.z;
    }
  }
}

void CubeCollisionUpdater::update(float dt, ParticleData *p) {
  size_t end_id = p->m_count_alive;

  auto pos = p->m_pos.get();
  auto prev = p->m_pos_prev.get();
  glm::vec3 mov,newpos, oldpos, ipos, clp,
          xnorm = glm::vec3(-1.f, 0.f, 0.f),
          ynorm = glm::vec3(0.f, -1.f, 0.f),
          znorm = glm::vec3(0.f, 0.f, -1.f);
  float dist = 0.5f;
  float xmin, xmax, ymin, ymax, zmin, zmax;

  bool help = false;
  for (size_t i = 0; i < end_id; ++i) {
    ipos = glm::vec3(pos[i]);
    clp = ipos;

    if(ipos.x < m_min.x) { clp.x = m_min.x;}
    else if(ipos.x > m_max.x) { clp.x = m_max.x;}
    if(ipos.y < m_min.y) { clp.y = m_min.y;}
    else if(ipos.y > m_max.y) { clp.y = m_max.y;}
    if(ipos.z < m_min.z) { clp.z = m_min.z;}
    else if(ipos.z > m_max.z) { clp.z = m_max.z;}

    if(clp != ipos){
      if(glm::length(clp - ipos) >= dist) continue;
      mov = ipos - clp;
      newpos = ipos + (dist - glm::length(mov)) * glm::normalize(mov);

    } else {
      glm::intersectRayPlane(ipos, xnorm, m_min, -xnorm, xmin);
      glm::intersectRayPlane(ipos, -xnorm, m_max, xnorm, xmax);
      if(xmin < xmax) { xnorm = xnorm * xmin;}
      else { xnorm = -xnorm * xmax;}

      glm::intersectRayPlane(ipos, ynorm, m_min, -ynorm, ymin);
      glm::intersectRayPlane(ipos, -ynorm, m_max, ynorm, ymax);
      if(ymin < ymax) { ynorm = ynorm * ymin;}
      else { ynorm = -ynorm * ymax;}

      glm::intersectRayPlane(ipos, znorm, m_min, -znorm, zmin);
      glm::intersectRayPlane(ipos, -znorm, m_max, znorm, zmax);
      if(zmin < zmax) { znorm = znorm * zmin;}
      else { znorm = -znorm * zmax;}

      if(glm::length(xnorm) > glm::length(ynorm)){
        if(glm::length(ynorm) > glm::length(znorm)){
          newpos = ipos + znorm + dist * glm::normalize(znorm);
        } else {
          newpos = ipos + ynorm + dist * glm::normalize(ynorm);
        }
      } else if(glm::length(xnorm) > glm::length(znorm)) {
        newpos = ipos + znorm + dist * glm::normalize(znorm);
      } else {
        newpos = ipos + xnorm + dist * glm::normalize(xnorm);
      }

    }
    pos[i] = glm::vec4(newpos, pos[i].w);
  }
}


void ClothCollisionUpdater::update(float dt, ParticleData *p){
  size_t end_id = p->m_count_alive;

  auto pos = p->m_pos.get();
  auto prev = p->m_pos_prev.get();
  glm::fvec3 dist, corr;
  float err;
  for(int k = 0; k < m_it; ++k) {
    for (size_t i = 0; i < end_id; ++i) {
      for (size_t j = i + 1; j < end_id; ++j) {
        if (m_collide[i][j]) {
          dist = glm::vec3(pos[i] - pos[j]);
          if(glm::length(dist) < m_dist){
            err = m_dist - glm::length(dist);

            corr = err * (1 - pos[i].w) * 0.5f * (1 + pos[j].w) * glm::normalize(dist);
            pos[i] += glm::vec4(corr, 0.f);
            corr = err * (1 - pos[j].w) * 0.5f * (1 + pos[i].w) * glm::normalize(dist);
            pos[j] -= glm::vec4(corr, 0.f);

          }

        }
      }
    }
  }
}

void GroundCollisionUpdater::update(float dt, ParticleData *p) {
  size_t end_id = p->m_count_alive;
  auto pos = p->m_pos.get();
  auto prev = p->m_pos_prev.get();

  glm::vec3 oldpos, mov;
  float dist;

  for (size_t i = 0; i < end_id; ++i) {
    if(pos[i].y < m_height){
      oldpos = glm::vec3(prev[i]);
      mov = glm::normalize(glm::vec3(pos[i]) - oldpos);
      glm::intersectRayPlane(oldpos, mov, glm::vec3(0.f, m_height, 0.f), glm::vec3(0.f, 1.f, 0.f), dist);
      pos[i] = glm::vec4(oldpos + mov * dist, pos[i].w);
    }
  }
}

void ClothCollisionUpdater::init(ParticleData *p) {
  size_t count = p->m_count;
  m_collide.clear();

  for(int i = 0; i < count; ++i){
    std::vector<bool> vec;
    for(int j = 0; j < count; ++j){
      if(i == j) { vec.push_back(false); }
      else { vec.push_back(true); }
    }
    m_collide.push_back(vec);
  }

  auto struc = p->m_struct_con;
  for(auto const& s : *struc){
    m_collide[(int)s.x][(int)s.y] = false;
    m_collide[(int)s.y][(int)s.x] = false;
  }
  auto shear = p->m_shear_con;
  for(auto const& s : *shear){
    m_collide[(int)s.x][(int)s.y] = false;
    m_collide[(int)s.y][(int)s.x] = false;
  }
  auto bend = p->m_bend_con;
  for(auto const& s : *bend){
    //m_collide[(int)s.x][(int)s.y] = false;
    //m_collide[(int)s.y][(int)s.x] = false;
  }
}

void WindForceUpdater::update(float dt, ParticleData *p) {
  auto tris = *p->m_indices.get();
  auto mass = p->m_mass.get();
  auto acc = p->m_acc.get();
  auto norm = p->m_normal.get();

  unsigned int x, y, z;
  glm::vec3 normal, f, w;

  w.x = m_wind.x * glm::linearRand(0.9f, 1.f);
  w.y = m_wind.y * glm::linearRand(0.9f, 1.f);
  w.z = m_wind.z * glm::linearRand(0.9f, 1.f);

  for(int i = 0; i < tris.size() / 3; ++i){
    x = tris[3 * i]; y = tris[3 * i + 1]; z = tris[3 * i + 2];

    normal = glm::normalize(glm::vec3(norm[x] + norm[y] + norm[z]));
    f = normal * glm::dot(w, normal);

    acc[x] += glm::vec4(f / mass[x], 0);
    acc[y] += glm::vec4(f / mass[y], 0);
    acc[z] += glm::vec4(f / mass[z], 0);
  }
}

void SpringColourUpdater::update(float dt, ParticleData *p) {
  size_t count = p->m_count;

  //reset colors
  auto col = p->m_col.get();
  auto pos = p->m_pos.get();
  for(unsigned int i = 0; i < count; ++i){
    col[i] = glm::vec4(0, 0, 0, 1);
  }
  //calc new colors
  float mix;
  int i,j;
  auto struc = p->m_struct_con.get();
  for(auto const& s : *struc){
    i = (int)s.x; j = (int)s.y;
    mix = (glm::length(glm::vec3(pos[i] - pos[j])) - m_min * s.z) / ((m_max - m_min) * s.z);
    col[i] += glm::vec4(glm::mix(m_minCol, m_maxCol, mix), 1);
    col[j] += glm::vec4(glm::mix(m_minCol, m_maxCol, mix), 1);
  }
  auto shear = p->m_shear_con.get();
  for(auto const& s : *shear){
    i = (int)s.x; j = (int)s.y;
    mix = (glm::length(glm::vec3(pos[i] - pos[j])) - m_min * s.z) / ((m_max - m_min) * s.z);
    col[i] += glm::vec4(glm::mix(m_minCol, m_maxCol, mix), 1);
    col[j] += glm::vec4(glm::mix(m_minCol, m_maxCol, mix), 1);
  }
  auto bend = p->m_bend_con.get();
  for(auto const& s : *bend){
    i = (int)s.x; j = (int)s.y;
    mix = (glm::length(glm::vec3(pos[i] - pos[j])) - m_min * s.z) / ((m_max - m_min) * s.z);
    col[i] += glm::vec4(glm::mix(m_minCol, m_maxCol, mix), 1);
    col[j] += glm::vec4(glm::mix(m_minCol, m_maxCol, mix), 1);
  }

  for(unsigned int i = 0; i < count; ++i){
    col[i] = glm::vec4(glm::normalize(glm::vec3(col[i])), 1);
  }
}

void AirResistanceUpdater::update(float dt, ParticleData *p) {
  size_t count = p->m_count;

  auto acc = p->m_acc.get();
  auto pos = p->m_pos.get();
  auto prev = p->m_pos_prev.get();

  glm::vec3 vel;

  for(unsigned int i = 0; i < count; ++i){
    vel = glm::vec3(pos[i] - prev[i]);
    if(glm::length(vel) > 0) {
      acc[i] += glm::vec4((-m_a * glm::normalize(vel) * glm::length(vel)), 0.f);
    }
  }
}

