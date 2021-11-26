import { TestBed } from '@angular/core/testing';

import { DoorlockServiceService } from './doorlock.service';

describe('DoorlockServiceService', () => {
  let service: DoorlockServiceService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(DoorlockServiceService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
