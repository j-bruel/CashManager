import unittest
import os
import json
from server_bank import app, db

class BucketlistTestCase(unittest.TestCase):
    """This class represents the bucketlist test case"""

    def setUp(self):
        """Define test variables and initialize app."""
        self.app = app
        self.client = self.app.test_client
        self.bucketlist = {'name': 'Go to Borabora for vacation'}
        # binds the app to the current context
        with self.app.app_context():
            # create all tables
            db.create_all()

    def test_bucketlist_deletion(self):
            """."""
            # rv = self.client().post(
            #     '/bucketlists/',
            #     data={'name': 'Eat, pray and love'})
            # self.assertEqual(rv.status_code, 201)
            # res = self.client().delete('/bucketlists/1')
            # self.assertEqual(res.status_code, 200)
            # # Test to see if it exists, should return a 404
            # result = self.client().get('/bucketlists/1')
            # self.assertEqual(result.status_code, 404)

    def tearDown(self):
        """teardown all initialized variables."""
        with self.app.app_context():
            # drop all tables
            db.session.remove()
            db.drop_all()


# Make the tests conveniently executable
if __name__ == "__main__":
    unittest.main()
