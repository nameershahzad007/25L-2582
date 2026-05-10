#include "../include/Storage.h"
#include "../include/Admin.h"
#include "../include/Appointment.h"
#include "../include/Bill.h"
#include "../include/Doctor.h"
#include "../include/Patient.h"
#include "../include/Prescription.h"

template class Storage<Admin>;
template class Storage<Appointment>;
template class Storage<Bill>;
template class Storage<Doctor>;
template class Storage<Patient>;
template class Storage<Prescription>;
